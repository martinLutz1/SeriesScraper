#include "controller.h"
#include <QDebug>
#include <vector>

void Controller::initializeNameSchemes()
{
    QStringList nameSchemeRepresentationList;
    QStringList nameSchemeList;
    bool fileRead = nameSchemeHandler.readNameSchemeFile();
    int amountNameSchemes = nameSchemeHandler.getAmountNameSchemes();

    // Read all name schemes
    if (fileRead && amountNameSchemes > 0)
    {
        for (int i = 0; i < amountNameSchemes; i++)
        {
            nameSchemeHandler.setNameScheme(i);
            nameSchemeRepresentationList <<  nameSchemeHandler.getNameSchemeRepresentation();
            nameSchemeList << nameSchemeHandler.getNameScheme(i);

        }
    } else // Add default entry if name scheme list not found or empty
    {
        nameSchemeHandler.addNameScheme("%$series% - S%$season(2)%E%$episode(2)% - %$episodeName%");
        nameSchemeRepresentationList << nameSchemeHandler.getNameSchemeRepresentation();
        // Error message
        QString nameSchemeFileNotFound = languageControl.getTranslation(LanguageData::nameSchemeFileNotFound);
        setStatusMessage(nameSchemeFileNotFound);
    }

    // Send name scheme list to view
    Message msgAddNameSchemes;
    msgAddNameSchemes.type = Message::controller_addNameSchemes_view;
    msgAddNameSchemes.data[0].qsListPointer = &nameSchemeRepresentationList;
    emit(sendMessage(msgAddNameSchemes));

    // Send raw name scheme list to settings
    Message msgSetRawNameSchemes;
    msgSetRawNameSchemes.type = Message::controller_setRawNameSchemes_settings;
    msgSetRawNameSchemes.data[0].qsListPointer = &nameSchemeList;
    emit(sendMessage(msgSetRawNameSchemes));
}

void Controller::initializeSeriesLanguages()
{
    bool fileRead = seriesLanguage.loadSeriesLanguageFile();
    QStringList seriesLanguageList = seriesLanguage.getLanguageList();

    // Add default entry if series language file not found or empty
    if (!fileRead || seriesLanguageList.empty())
    {
        seriesLanguageList << QString("English");
        // Error message
        QString languageFileReadingFailure = languageControl.getTranslation(LanguageData::seriesLanguageNotFound);
        setStatusMessage(languageFileReadingFailure);
    }

    // Send series language list to view
    Message msgAddSeriesLanguages;
    msgAddSeriesLanguages.type = Message::controller_addSeriesLanguages_view;
    msgAddSeriesLanguages.data[0].qsListPointer = &seriesLanguageList;
    emit(sendMessage(msgAddSeriesLanguages));

    QString languageShortName = seriesLanguage.getShortName(0); // Settings
    seriesData.setSelectedLanguage(languageShortName); // Settings
}

void Controller::initializeGUILanguages()
{
    bool languageInitSuccess = languageControl.initialize();
    if (languageInitSuccess)
    {
        QStringList guiLanguageList = languageControl.getLanguageList();
        // Send gui language list to settings
        Message msgAddGUILanguages;
        msgAddGUILanguages.type = Message::controller_addGUILanguages_settings;
        msgAddGUILanguages.data[0].qsListPointer = &guiLanguageList;
        emit(sendMessage(msgAddGUILanguages));
    } else // No language files found
    {
        Message msgNoGUILanguagesFound;
        msgNoGUILanguagesFound.type = Message::controller_noGUILanguagesFound_settings;
        emit(sendMessage(msgNoGUILanguagesFound));
        // Error message
        setStatusMessage("No language files found");
    }
}

void Controller::initializeSettings()
{
    int selectedSeriesParser = settings.getSeriesDatabase();
    int selectedNameScheme = settings.getNameScheme();
    QString selectedGuiLanguage = settings.getGuiLanguage();
    QString selectedSeriesLanguage = settings.getSeriesLanguage();
    bool saveSeries = settings.getSaveSeries();
    bool savePath = settings.getSavePath();
    bool useDarkTheme = settings.getDarkTheme();

    changeGuiLanguage(selectedGuiLanguage);
    changeSeriesParser(selectedSeriesParser);
    changeNameScheme(selectedNameScheme);
    changeSeriesLanguage(selectedSeriesLanguage);
    changeSaveSeries(saveSeries);
    changeSavePath(savePath);

    Message msgUseDarkTheme;
    msgUseDarkTheme.type = Message::controller_useDarkTheme_settings;
    msgUseDarkTheme.data[0].b = useDarkTheme;
    emit(sendMessage(msgUseDarkTheme));
}

void Controller::updateNewFileNames()
{
    QString series = seriesData.getSeries();
    int season = seriesData.getSelectedSeason();
    int amountEpisodes = seriesData.getAmountEpisodes();
    QStringList episodeList = seriesData.getEpisodes();
    QStringList suffixList = seriesData.getSuffixes();

    QStringList newFileNames;
    QStringList newFileNamesWithoutSuffix = nameSchemeHandler.getFileNameList(series, season, amountEpisodes, episodeList);

    int minimumSize = std::min(newFileNamesWithoutSuffix.size(), suffixList.size());
    for (int i = 0; i < minimumSize; i++)
        newFileNames << (newFileNamesWithoutSuffix.at(i) + "." + suffixList.at(i));

    seriesData.setNewFileNames(newFileNames);
    seriesData.setNewFileNamesWithoutSuffix(newFileNamesWithoutSuffix);
}

void Controller::setStatusMessage(QString status)
{
    Message msgSetStatus;
    msgSetStatus.type = Message::controller_setStatus_view;
    msgSetStatus.data[0].qsPointer =  &status;
    emit(sendMessage(msgSetStatus));
}

Controller::Controller(QObject *parent) : QObject(parent)
{
}

Controller::~Controller()
{
    bool saveSeries = settings.getSaveSeries();
    bool savePath = settings.getSavePath();
    if (saveSeries)
    {
        QString series = seriesParser.getSeriesInput();
        int season = seriesData.getSelectedSeason();
        settings.setSeries(series);
        settings.setSeason(season);
    } else
    {
        settings.setSeries("");
        settings.setSeason(1);
    }

    if (savePath)
    {
        QString path = directoryParser.getDirectoryPathInput();
        settings.setPath(path);
    } else
        settings.setPath("");

    settings.saveSettingsFile();
}

void Controller::initialize()
{
    settings.loadSettingsFile();

    // Dont change theme afterwards!
    bool useDarkTheme = settings.getDarkTheme();
    if (useDarkTheme)
    {
        Message msgUseDarkTheme;
        msgUseDarkTheme.type = Message::controller_useDarkTheme_view;
        emit(sendMessage(msgUseDarkTheme));
    }

    initializeGUILanguages();
    initializeNameSchemes();
    initializeSeriesLanguages();
    initializeSettings();
}

bool Controller::loadSeries(QString series, int season)
{
    // Set default values
    QString newSeriesName("");
    int newSelectedSeason = 1;
    int newAmountSeasons = 0;
    QStringList newEpisodeList;
    bool seriesFound = false;

    // Dont scrape the empty string
    bool seriesStringNotEmpty = !series.isEmpty();
    if (seriesStringNotEmpty)
    {
        // Start loading animation
        Message msgStartLoading;
        msgStartLoading.type = Message::controller_startSeriesLoading_view;
        emit(sendMessage(msgStartLoading));

        seriesFound = seriesParser.scrapeSeries(series);
        if (seriesFound)
        {
            QString seriesLanguage = seriesData.getSelectedLanguage();
            newSelectedSeason = season;
            newSeriesName = seriesParser.getSeriesName();
            newAmountSeasons = seriesParser.getAmountSeasons();
            newEpisodeList = seriesParser.getEpisodeList(season, seriesLanguage);

            // Finish loading animation
            Message msgSuccessLoading;
            msgSuccessLoading.type = Message::controller_successSeriesLoading_view;
            emit(sendMessage(msgSuccessLoading));
        } else // No series found
        {
            // Finish loading animation with failure message
            Message msgFailureLoading;
            msgFailureLoading.type = Message::controller_failureSeriesLoading_view;
            emit(sendMessage(msgFailureLoading));
        }
    }
    else
        seriesParser.scrapeSeries(series); // Reset

    seriesData.setSeries(newSeriesName);
    seriesData.setAmountSeasons(newAmountSeasons);
    seriesData.setSelectedSeason(newSelectedSeason);
    seriesData.setEpisodes(newEpisodeList);
    updateNewFileNames();
    updateView();
    return seriesFound;
}

bool Controller::changeSeason(int season)
{
    QString series = seriesParser.getSeriesInput();
    return loadSeries(series, season);
}

bool Controller::changeGuiLanguage(QString language)
{
    bool loadingSuccessful = languageControl.loadLanguage(language);
    QString guiLanguage = "English";
    if (loadingSuccessful)
    {
        guiLanguage = language;
        QStringList translationList = languageControl.getTranslationList();
        // Send translations to view, about and settings
        Message msgChangeLocalization;
        msgChangeLocalization.type = Message::controller_changeLocalization_view;
        msgChangeLocalization.data[0].qsListPointer = &translationList;
        msgChangeLocalization.data[1].qsPointer = &language;
        emit(sendMessage(msgChangeLocalization));
    } else
    {
        // Error message
        setStatusMessage("Could not read language file " + language + ".json");
    }

    settings.setGuiLanguage(guiLanguage);
    return loadingSuccessful;
}

void Controller::changeSeriesLanguage(QString language)
{
    Message msgChangeSeriesLanguage;
    msgChangeSeriesLanguage.type = Message::controller_changeSeriesLanguage_view;
    msgChangeSeriesLanguage.data[0].qsPointer = &language;
    emit(sendMessage(msgChangeSeriesLanguage));

    QString selectedLanguage = seriesLanguage.getShortName(language);
    seriesData.setSelectedLanguage(selectedLanguage);
    settings.setSeriesLanguage(language);
    QString series = seriesParser.getSeriesInput();
    int season = seriesData.getSelectedSeason();
    loadSeries(series, season);
}

void Controller::changeSeriesParser(int selectedSeriesParser)
{
    Message msgChangeSeriesParser;
    msgChangeSeriesParser.type = Message::controller_changeSeriesParser_view;
    msgChangeSeriesParser.data[0].i = selectedSeriesParser;
    emit(sendMessage(msgChangeSeriesParser));

    int oldSeriesParser = seriesParser.getSeriesParser();
    if (selectedSeriesParser != oldSeriesParser)
    {
        QString series = seriesParser.getSeriesInput();
        int season = seriesData.getSelectedSeason();
        seriesParser.setSeriesParser(selectedSeriesParser);
        settings.setSeriesDatabase(selectedSeriesParser);
        if (!series.isEmpty())
            loadSeries(series, season);
    }
}

void Controller::changeSeries(QString series, int season)
{
    bool isEmpty = series.isEmpty();
    bool seriesSet = loadSeries(series, season);

    // Send scraping status to view
    Message msgSeriesSet;
    msgSeriesSet.type = Message::controller_seriesSet_view;
    msgSeriesSet.data[0].b = seriesSet;
    msgSeriesSet.data[1].b = isEmpty;
    emit(sendMessage(msgSeriesSet));
}

void Controller::changeSaveSeries(bool saveSeries)
{
    if (saveSeries)
    {
        QString series = settings.getSeries();
        int season = settings.getSeason();
        changeSeries(series, season);

        Message msgSetSeries;
        msgSetSeries.type = Message::controller_setSeries_view;
        msgSetSeries.data[0].qsPointer = &series;
        msgSetSeries.data[1].i = season;
        emit(sendMessage(msgSetSeries));
    }
    Message msgSaveSeries;
    msgSaveSeries.type = Message::controller_saveSeries_settings;
    msgSaveSeries.data[0].b = saveSeries;
    emit(sendMessage(msgSaveSeries));
}

void Controller::changeSavePath(bool savePath)
{
    if (savePath)
    {
        QString path = settings.getPath();
        Message msgSetPath;
        msgSetPath.type = Message::controller_setPath_view;
        msgSetPath.data[0].qsPointer = &path;
        emit(sendMessage(msgSetPath));
    }
    Message msgSavePath;
    msgSavePath.type = Message::controller_savePath_settings;
    msgSavePath.data[0].b = savePath;
    emit(sendMessage(msgSavePath));
}

void Controller::changeNameScheme(int nameScheme)
{
    int amountNameSchemes = nameSchemeHandler.getAmountNameSchemes();
    int newNameScheme = 0;

    if (nameScheme < amountNameSchemes)
        newNameScheme = nameScheme;
    else
    {
        QString nameSchemeLineNotFound = languageControl.getTranslation(LanguageData::nameSchemeLineNotFound);
        setStatusMessage(nameSchemeLineNotFound + " " +  QString::number(nameScheme + 1));
    }

    settings.setNameScheme(newNameScheme);
    nameSchemeHandler.setNameScheme(newNameScheme);
    Message msgChangeNameScheme;
    msgChangeNameScheme.type = Message::controller_changeNameScheme_view;
    msgChangeNameScheme.data[0].i = newNameScheme;
    emit(sendMessage(msgChangeNameScheme));
}

bool Controller::setDirectory(QString path)
{
    bool directoryExists = directoryParser.initializeDirectory(path);
    QDir newDirectory("");
    QStringList newOldFileNames;
    QStringList newOldFileNamesWithoutSuffixes;
    QStringList newSuffixes;

    // Update directory and file infos
    if (directoryExists)
    {
        newDirectory = QDir(path);
        newOldFileNames = directoryParser.getFiles();
        newSuffixes = directoryParser.getFilesSuffix();
        newOldFileNamesWithoutSuffixes = directoryParser.getFilesWithoutSuffix();
    }

    seriesData.setWorkingDirectory(newDirectory);
    seriesData.setOldFileNames(newOldFileNames);
    seriesData.setOldFileNamesWithoutSuffix(newOldFileNamesWithoutSuffixes);
    seriesData.setSuffixes(newSuffixes);

    return directoryExists;
}

bool Controller::renameFiles()
{
    QDir directory = seriesData.getWorkingDirectory();
    QStringList newFileNameList = seriesData.getNewFileNames();
    QStringList oldFileNameList = seriesData.getOldFileNames();

    fileRenamer.setDirectory(directory);
    fileRenamer.setOldFileNames(oldFileNameList);
    fileRenamer.setNewFileNames(newFileNameList);
    bool renameSuccess = fileRenamer.rename();

    if (renameSuccess)
    {
        QStringList renamedFiles = directoryParser.getFiles();
        QStringList renamedFilesWithoutSuffix = directoryParser.getFilesWithoutSuffix();
        seriesData.setOldFileNames(renamedFiles);
        seriesData.setOldFileNamesWithoutSuffix(renamedFilesWithoutSuffix);
        updateView();

        // Success Message
        QString renameSuccessful = languageControl.getTranslation(LanguageData::renameSuccess);
        setStatusMessage(renameSuccessful);
    } else
    {
        // Failure Message
        QString renameFailure = languageControl.getTranslation(LanguageData::renameFailed);
        setStatusMessage(renameFailure);
    }
    return renameSuccess;
}

void Controller::updateView()
{
    QStringList newFileNameList = seriesData.getNewFileNamesWithoutSuffix();
    QStringList oldFileNameList = seriesData.getOldFileNamesWithoutSuffix();
    int amountSeasons = seriesData.getAmountSeasons();

    Message msgViewUpdate;
    msgViewUpdate.type = Message::controller_updateView_view;
    msgViewUpdate.data[0].i = amountSeasons;
    msgViewUpdate.data[1].qsListPointer = &oldFileNameList;
    msgViewUpdate.data[2].qsListPointer = &newFileNameList;
    emit(sendMessage(msgViewUpdate));
    updateRenameButton();
}

void Controller::updateRenameButton()
{
    QDir testDir("");
    bool differentFileNames = false;
    QStringList oldNames = seriesData.getOldFileNames();
    QStringList newNames = seriesData.getNewFileNames();
    int minimumSize = std::min(oldNames.size(), newNames.size());
    for (int i = 0; i < minimumSize; i ++)
    {
        bool differentNames = (oldNames.at(i) != newNames.at(i));
        bool oldNameIsEmpty = oldNames.at(i).isEmpty();
        bool newNameIsEmpty = newNames.at(i).isEmpty();
        if (differentNames && !oldNameIsEmpty && !newNameIsEmpty)
        {
            differentFileNames = true;
            break;
        }
    }

    bool directorySet = (seriesData.getWorkingDirectory().absolutePath() != testDir.absolutePath());
    bool seriesSet = !seriesData.getSeries().isEmpty();
    bool enableButton = seriesSet & directorySet & differentFileNames;

    Message msgEnableButton;
    msgEnableButton.type = Message::controller_enableButton_view;
    msgEnableButton.data[0].b = enableButton;
    emit(sendMessage(msgEnableButton));
}

void Controller::notify(Message &msg)
{
    switch (msg.type)
    {
    case Message::view_changeSeriesText_controller:
    {
        QString series = *msg.data[0].qsPointer;
        QString oldSeries = seriesParser.getSeriesInput();
        // Only write on change
        if (series != oldSeries)
        {
            changeSeries(series, 1);
        }
        break;
    }
    case Message::view_changeSeason_controller:
    {
        int selectedSeason = msg.data[0].i;
        int oldSelectedSeason = seriesData.getSelectedSeason();
        // Only write on change
        if (selectedSeason != oldSelectedSeason)
            changeSeason(selectedSeason);
        break;
    }
    case Message::view_changeSeriesLanguage_controller:
    {
        int languageIndex = msg.data[0].i;
        QString language = seriesLanguage.getLanguageList().at(languageIndex);
        QString languageShortName = seriesLanguage.getShortName(languageIndex + 1);
        QString oldLanguageShortName = seriesData.getSelectedLanguage();
        // Only write on change
        if (oldLanguageShortName != languageShortName)
            changeSeriesLanguage(language);
        break;
    }
    case Message::view_changeDirectory_controller:
    {
        QString path = *msg.data[0].qsPointer;
        setDirectory(path);
        updateNewFileNames();
        updateView();
        break;
    }
    case Message::view_changeEpisodeName_controller:
    {
        int episode = msg.data[0].i;
        QString newEpisodeName = *msg.data[1].qsPointer;
        QString oldEpisodeName = seriesData.getEpisode(episode);
        if (oldEpisodeName != newEpisodeName) // Only write on change
        {
            seriesData.setEpisode(episode, newEpisodeName);
            updateNewFileNames();
            updateView();
        }
        break;
    }
    case Message::view_getEpisodeName_controller:
    {
        int episode = msg.data[0].i;
        QString episodeName = seriesData.getEpisode(episode);

        Message msgReturnEpisodeName;
        msgReturnEpisodeName.type = Message::controller_returnEpisodeName_view;
        msgReturnEpisodeName.data[0].qsPointer = &episodeName;
        emit(sendMessage(msgReturnEpisodeName));
        break;
    }
    case Message::view_rename_controller:
    {
        int foundSeason = directoryParser.getFoundSeason();
        int selectedSeason =  seriesData.getSelectedSeason();

        if (foundSeason == 0 || foundSeason == selectedSeason)
            renameFiles();
        else
        {
            Message msgSeasonMismatch;
            msgSeasonMismatch.type = Message::controller_seasonMismatch_view;
            emit(sendMessage(msgSeasonMismatch));
        }
        break;
    }
    case Message::view_forceRename_controller:
    {
        renameFiles();
        break;
    }
    case Message::view_changeNameScheme_controller:
    {
        int selectedNameScheme = msg.data[0].i;
        changeNameScheme(selectedNameScheme);
        updateNewFileNames();
        updateView();
        break;
    }
    case Message::settings_changeGUILanguage_controller:
    {
        QString language = *msg.data[0].qsPointer;
        changeGuiLanguage(language);
        break;
    }
    case Message::view_showAboutDialog_controller:
    {
        Message msgShowAboutDialog;
        msgShowAboutDialog.type = Message::controller_showAboutDialog_about;
        emit(sendMessage(msgShowAboutDialog));
        break;
    }
    case Message::view_showSettingsWindow_controller:
    {
        Message msgShowSettingsDialog;
        msgShowSettingsDialog.type = Message::controller_showSettingsWindow_settings;
        emit(sendMessage(msgShowSettingsDialog));
        break;
    }
    case Message::settings_changeSeriesParser_controller:
    {
        int selectedSeriesParser = msg.data[0].i;
        changeSeriesParser(selectedSeriesParser);
        break;
    }
    case Message::settings_saveSeries_controller:
    {
        bool saveSeries = msg.data[0].b;
        settings.setSaveSeries(saveSeries);
        break;
    }
    case Message::settings_savePath_controller:
    {
        bool savePath = msg.data[0].b;
        settings.setSavePath(savePath);
        break;
    }
    case Message::settings_reset_controller:
    {
        settings.resetSettingsFile();
        initializeSettings();
        break;
    }
    case Message::settings_useDarkTheme_controller:
    {
        bool useDarkTheme = msg.data[0].b;
        settings.setDarkTheme(useDarkTheme);
        break;
    }
    default:
        break;
    }
}
