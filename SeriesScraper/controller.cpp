#include "controller.h"

#include "episodename.h"
#include <QDebug>
#include <vector>

void Controller::initializeFileTypes()
{
    bool loadingSuccessful = fileTypeHandler.loadFileTypeFile();

    QStringList fileTypes = fileTypeHandler.getFileTypes();
    directoryHandler->setFileTypes(fileTypes);

    Message msgSetFileTypes;
    msgSetFileTypes.type = Message::Type::controller_setFileTypes_settings;
    msgSetFileTypes.data[0].qsListPointer = &fileTypes;
    emit(sendMessage(msgSetFileTypes));

    if (!loadingSuccessful)
    {
        QString fileFormatNotFound = interfaceLanguageHandler.getTranslation(
                    LanguageData::Translate::fileFormatNotFound);
        setStatusMessage(fileFormatNotFound, MainWindow::StatusMessageType::error);
    }
}

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
            nameSchemeList << nameSchemeHandler.getNameScheme();
        }
    } else // Add default entry if name scheme list not found or empty
    {
        nameSchemeHandler.addNameScheme("|Simple| <series> - S<season(2)>E<episode(2)> - <episodeName>");
        nameSchemeRepresentationList << nameSchemeHandler.getNameSchemeRepresentation();
        // Error message
        QString nameSchemeFileNotFound = interfaceLanguageHandler.getTranslation(
                    LanguageData::Translate::nameSchemeFileNotFound);
        setStatusMessage(nameSchemeFileNotFound, MainWindow::StatusMessageType::error);
    }

    // Send name scheme list to view
    Message msgAddNameSchemes;
    msgAddNameSchemes.type = Message::Type::controller_addNameSchemes_view;
    msgAddNameSchemes.data[0].qsListPointer = &nameSchemeRepresentationList;
    emit(sendMessage(msgAddNameSchemes));

    // Send raw name scheme list to settings
    Message msgSetRawNameSchemes;
    msgSetRawNameSchemes.type = Message::Type::controller_setRawNameSchemes_settings;
    msgSetRawNameSchemes.data[0].qsListPointer = &nameSchemeList;
    emit(sendMessage(msgSetRawNameSchemes));
}

void Controller::initializeSeriesLanguages()
{
    bool fileRead = seriesLanguageHandler.loadSeriesLanguageFile();
    QStringList seriesLanguageList = seriesLanguageHandler.getLanguageList();

    // Add default entry if series language file not found or empty
    if (!fileRead || seriesLanguageList.empty())
    {
        seriesLanguageList << QString("English");
        // Error message
        QString languageFileReadingFailure = interfaceLanguageHandler.getTranslation(
                    LanguageData::Translate::seriesLanguageNotFound);
        setStatusMessage(languageFileReadingFailure, MainWindow::StatusMessageType::error);
    }

    // Send series language list to view
    Message msgAddSeriesLanguages;
    msgAddSeriesLanguages.type = Message::Type::controller_addSeriesLanguages_view;
    msgAddSeriesLanguages.data[0].qsListPointer = &seriesLanguageList;
    emit(sendMessage(msgAddSeriesLanguages));

    QString languageShortName = seriesLanguageHandler.getShortName(0); // Settings
    seriesData.setSelectedLanguage(languageShortName); // Settings
}

void Controller::initializeInterfaceLanguages()
{
    bool languageInitSuccess = interfaceLanguageHandler.initialize();
    if (languageInitSuccess)
    {
        QStringList interfaceLanguageList = interfaceLanguageHandler.getLanguageList();
        // Send gui language list to settings
        Message msgAddGUILanguages;
        msgAddGUILanguages.type = Message::Type::controller_addGUILanguages_settings;
        msgAddGUILanguages.data[0].qsListPointer = &interfaceLanguageList;
        emit(sendMessage(msgAddGUILanguages));
    } else // No language files found
    {
        Message msgNoGUILanguagesFound;
        msgNoGUILanguagesFound.type = Message::Type::controller_noGUILanguagesFound_settings;
        emit(sendMessage(msgNoGUILanguagesFound));
        // Error message
        setStatusMessage("No language files found", MainWindow::StatusMessageType::error);
    }
}

void Controller::initializeSettings()
{
    settings.loadSettingsFile();

    auto selectedSeriesParser = (SeriesParser::Parser)settings.getSeriesDatabase();
    int selectedNameScheme = settings.getNameScheme();
    QString selectedInterfaceLanguage = settings.getGuiLanguage();
    QString selectedSeriesLanguage = settings.getSeriesLanguage();
    bool saveSeries = settings.getSaveSeries();
    bool savePath = settings.getSavePath();
    bool savePosterInDirectory = settings.getSavePosterInDirectory();
    bool setDetectedSeason = settings.getAutoSetDetectedSeason();
    bool useDarkTheme = settings.getDarkTheme();
    bool showSeriesInfo = settings.getShowSeriesInfo();
    QRect windowRect = settings.getWindowRect();

    // Dont change theme afterwards!
    if (useDarkTheme)
    {
        Message msgUseDarkTheme;
        msgUseDarkTheme.type = Message::Type::controller_useDarkTheme_view;
        emit(sendMessage(msgUseDarkTheme));
    }

    changeInterfaceLanguage(selectedInterfaceLanguage);
    changeSeriesParser(selectedSeriesParser);
    changeNameScheme(selectedNameScheme);
    changeSeriesLanguage(selectedSeriesLanguage);
    changeSaveSeries(saveSeries);
    changeSavePath(savePath);

    Message msgSavePosterInDirectory;
    msgSavePosterInDirectory.type = Message::Type::controller_savePoster_settings;
    msgSavePosterInDirectory.data[0].b = savePosterInDirectory;
    emit(sendMessage(msgSavePosterInDirectory));

    Message msgSetDetectedSeason;
    msgSetDetectedSeason.type = Message::Type::controller_setDetectedSeason_settings;
    msgSetDetectedSeason.data[0].b = setDetectedSeason;
    emit(sendMessage(msgSetDetectedSeason));

    Message msgUseDarkTheme;
    msgUseDarkTheme.type = Message::Type::controller_useDarkTheme_settings;
    msgUseDarkTheme.data[0].b = useDarkTheme;
    emit(sendMessage(msgUseDarkTheme));

    Message msgShowSeriesInfo;
    msgShowSeriesInfo.type = Message::Type::controller_showSeriesInfo_settings;
    msgShowSeriesInfo.data[0].b = showSeriesInfo;
    emit(sendMessage(msgShowSeriesInfo));

    Message msgSetWindowRect;
    msgSetWindowRect.type = Message::Type::controller_setWindowRect_view;
    msgSetWindowRect.data[0].qRectPointer = &windowRect;
    emit(sendMessage(msgSetWindowRect));
}

void Controller::updateNewFileNames()
{
    QString series = seriesData.getSeries();
    QString airDate = seriesData.getAirDate();
    int season = seriesData.getSelectedSeason();
    int amountEpisodes = seriesData.getAmountEpisodes();
    QStringList episodeList = seriesData.getEpisodes();

    QStringList newFileNamesWithoutSuffix = nameSchemeHandler.getFileNameList(series, airDate, season,
                                                                              amountEpisodes, episodeList);
    episodeNameHandler.setNewNames(newFileNamesWithoutSuffix);
}

void Controller::setStatusMessage(QString status, MainWindow::StatusMessageType type)
{
    Message msgSetStatus;
    msgSetStatus.type = Message::Type::controller_setStatus_view;
    msgSetStatus.data[0].qsPointer =  &status;
    msgSetStatus.data[1].i = (int)type;
    emit(sendMessage(msgSetStatus));
}

void Controller::setSeriesInformation()
{
    QByteArray *poster = nullptr;
    if (fileDownloader.downloadFile(seriesData.getPosterUrl()))
    {
        poster = fileDownloader.getDownloadedData();
    }
    QString totalEpisodes = QString::number(seriesData.getAmountEpisodes());
    auto season = seriesData.getSelectedSeason();
    QString seasonAsString = QString::number(season);
    QString totalSeasons = QString::number(seriesData.getAmountSeasons());
    QString seriesName = seriesData.getSeries();
    QString airDate = seriesData.getAirDate();
    QString plot = seriesData.getPlot();

    // Set default values for view, if no series set
    if (seriesName.isEmpty() && totalSeasons == "0")
    {
        poster = nullptr;
        totalEpisodes = "-";
        season = 0;
        seasonAsString = "-";
        totalSeasons = "-";
        seriesName = "";
        airDate = "-";
        plot = "";
    }

    // Update series info sidebar.
    Message msgSetSeriesInfo;
    msgSetSeriesInfo.type = Message::Type::controller_setSeriesInfo_view;
    msgSetSeriesInfo.data[0].qbPointer = poster;
    msgSetSeriesInfo.data[1].qsPointer = &totalEpisodes;
    msgSetSeriesInfo.data[2].qsPointer = &seasonAsString;
    msgSetSeriesInfo.data[3].qsPointer = &totalSeasons;
    msgSetSeriesInfo.data[4].qsPointer = &seriesName;
    msgSetSeriesInfo.data[5].qsPointer = &airDate;
    msgSetSeriesInfo.data[6].qsPointer = &plot;
    emit(sendMessage(msgSetSeriesInfo));

    // Update selected season.
    Message msgSetSeason;
    msgSetSeason.type = Message::Type::controller_setSeason_view;
    msgSetSeason.data[0].i = season;
    emit(sendMessage(msgSetSeason));
}

Controller::Controller(QObject *parent) : QObject(parent)
{
    directoryHandler = new DirectoryHandler;
    directoryHandler->moveToThread(&workerThreadDirectory);

    connect(this, SIGNAL(initializeDirectory(QString)), directoryHandler, SLOT(initializeDirectory(QString)));
    connect(this, SIGNAL(rename()), directoryHandler, SLOT(rename()));
    connect(this, SIGNAL(undoRename()), directoryHandler, SLOT(undoRename()));
    connect(directoryHandler, SIGNAL(directoryInitialized(bool)), this, SLOT(directorySet(bool)));
    connect(directoryHandler, SIGNAL(renameDone(bool)), this, SLOT(renameDone(bool)));
    connect(directoryHandler, SIGNAL(undoRenameDone(bool)), this, SLOT(undoRenameDone(bool)));
    connect(directoryHandler, SIGNAL(updateRenameProgress(int,int,QString,QString)),
            this, SLOT(renameProgressUpdate(int,int,QString,QString)));

    workerThreadDirectory.start();
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
    }
    else
    {
        settings.setSeries("");
        settings.setSeason(1);
    }

    if (savePath)
    {
        QString path = directoryHandler->getDirectoryPathInput();
        settings.setPath(path);
    }
    else
    {
        settings.setPath("");
    }

    settings.saveSettingsFile();
    workerThreadDirectory.quit();
    workerThreadDirectory.wait();
}

void Controller::initialize()
{
    initializeFileTypes();
    initializeSeriesLanguages();
    initializeInterfaceLanguages();
    initializeNameSchemes();
    initializeSettings();
}

bool Controller::loadSeries(QString series, int season)
{
    // Set default values
    QString newPosterUrl("");
    QString newSeriesName("");
    QString newAirDate("");
    QString newPlot("");
    int newSelectedSeason(1);
    int newAmountSeasons(0);
    QStringList newEpisodeList;
    bool seriesFound(false);

    // Dont scrape an empty string
    if (!series.isEmpty())
    {
        // Start loading animation
        Message msgStartLoading;
        msgStartLoading.type = Message::Type::controller_startSeriesLoading_view;
        emit(sendMessage(msgStartLoading));

        seriesParser.setSeriesInput(series);
        seriesFound = seriesParser.getSeriesParser()->scrapeSeries(series);
        if (seriesFound)
        {
            QString seriesLanguage = seriesData.getSelectedLanguage();
            newAmountSeasons = seriesParser.getSeriesParser()->getAmountSeasons();

            int seasonToLoad = season;
            if (season > newAmountSeasons) // Avoid loading not existing seasons
            {
                seasonToLoad = 1;
            }
            newEpisodeList = seriesParser.getSeriesParser()->getSeason(seasonToLoad, seriesLanguage);
            newSelectedSeason = seasonToLoad;
            newSeriesName = seriesParser.getSeriesParser()->getSeriesName();
            newPlot = seriesParser.getSeriesParser()->getPlot();
            newAirDate = seriesParser.getSeriesParser()->getYear();
            newPosterUrl = seriesParser.getSeriesParser()->getPosterUrl();
        }
    }
    else // Reset
    {
        seriesParser.setSeriesInput("");
        seriesParser.getSeriesParser()->scrapeSeries("");
    }

    seriesData.setSeries(newSeriesName);
    seriesData.setAirDate(newAirDate);
    seriesData.setPlot(newPlot);
    seriesData.setAmountSeasons(newAmountSeasons);
    seriesData.setSelectedSeason(newSelectedSeason);
    seriesData.setEpisodes(newEpisodeList);
    seriesData.setPosterUrl(newPosterUrl);

    if (settings.getShowSeriesInfo())
        setSeriesInformation();

    updateNewFileNames();
    updateView();

    // Send status to view
    if (seriesFound && !series.isEmpty())
    {
        Message msgSuccessLoading;
        msgSuccessLoading.type = Message::Type::controller_successSeriesLoading_view;
        emit(sendMessage(msgSuccessLoading));
    }
    else if (!seriesFound && !series.isEmpty())
    {
        Message msgFailureLoading;
        msgFailureLoading.type = Message::Type::controller_failureSeriesLoading_view;
        emit(sendMessage(msgFailureLoading));
    }
    return seriesFound;
}

bool Controller::changeSeason(int season)
{
    QString series = seriesParser.getSeriesInput();
    return loadSeries(series, season);
}

bool Controller::changeInterfaceLanguage(QString language)
{
    bool loadingSuccessful = interfaceLanguageHandler.loadLanguage(language);
    QString interfaceLanguage = "English";
    if (loadingSuccessful)
    {
        interfaceLanguage = language;
        QStringList translationList = interfaceLanguageHandler.getTranslationList();
        // Send translations to view, about and settings
        Message msgChangeLocalization;
        msgChangeLocalization.type = Message::Type::controller_changeLocalization_view;
        msgChangeLocalization.data[0].qsListPointer = &translationList;
        msgChangeLocalization.data[1].qsPointer = &language;
        emit(sendMessage(msgChangeLocalization));
    } else
    {
        // Error message
        setStatusMessage("Could not read language file " + language + ".json",
                         MainWindow::StatusMessageType::error);
    }

    settings.setGuiLanguage(interfaceLanguage);
    return loadingSuccessful;
}

void Controller::changeSeriesLanguage(QString language)
{
    Message msgChangeSeriesLanguage;
    msgChangeSeriesLanguage.type = Message::Type::controller_changeSeriesLanguage_view;
    msgChangeSeriesLanguage.data[0].qsPointer = &language;
    emit(sendMessage(msgChangeSeriesLanguage));

    QString selectedLanguage = seriesLanguageHandler.getShortName(language);
    seriesData.setSelectedLanguage(selectedLanguage);
    settings.setSeriesLanguage(language);
    QString series = seriesParser.getSeriesInput();
    int season = seriesData.getSelectedSeason();

    if (!series.isEmpty())
    {
        loadSeries(series, season);
    }
}

void Controller::changeSeriesParser(SeriesParser::Parser selectedSeriesParser)
{
    Message msgChangeSeriesParser;
    msgChangeSeriesParser.type = Message::Type::controller_changeSeriesParser_view;
    msgChangeSeriesParser.data[0].i = (int)selectedSeriesParser;
    emit(sendMessage(msgChangeSeriesParser));

    auto oldSeriesParser = seriesParser.getSeriesParserIndex();
    if (selectedSeriesParser != oldSeriesParser)
    {
        QString series = seriesParser.getSeriesInput();
        int season = seriesData.getSelectedSeason();
        seriesParser.setSeriesParser(selectedSeriesParser);
        settings.setSeriesDatabase(selectedSeriesParser);

        if (!series.isEmpty())
        {
            loadSeries(series, season);
        }
    }
}

void Controller::changeSeries(QString series, int season)
{
    bool isEmpty = series.isEmpty();
    bool seriesSet = loadSeries(series, season);

    // Send scraping status to view
    Message msgSeriesSet;
    msgSeriesSet.type = Message::Type::controller_seriesSet_view;
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
        msgSetSeries.type = Message::Type::controller_setSeries_view;
        msgSetSeries.data[0].qsPointer = &series;
        msgSetSeries.data[1].i = season;
        emit(sendMessage(msgSetSeries));
    }
    Message msgSaveSeries;
    msgSaveSeries.type = Message::Type::controller_saveSeries_settings;
    msgSaveSeries.data[0].b = saveSeries;
    emit(sendMessage(msgSaveSeries));
}

void Controller::changeSavePath(bool savePath)
{
    if (savePath)
    {
        setDirectory(settings.getPath());
    }
    else
    {
        setDirectory(QDir::homePath());
    }

    Message msgSavePath;
    msgSavePath.type = Message::Type::controller_savePath_settings;
    msgSavePath.data[0].b = savePath;
    emit(sendMessage(msgSavePath));
}

void Controller::changeNameScheme(int nameScheme)
{
    int amountNameSchemes = nameSchemeHandler.getAmountNameSchemes();
    int newNameScheme = 0;

    if (nameScheme < amountNameSchemes)
    {
        newNameScheme = nameScheme;
    }
    else
    {
        QString nameSchemeLineNotFound = interfaceLanguageHandler.getTranslation(
                    LanguageData::Translate::nameSchemeLineNotFound);
        setStatusMessage(nameSchemeLineNotFound + " " + QString::number(nameScheme + 1),
                         MainWindow::StatusMessageType::error);
    }

    settings.setNameScheme(newNameScheme);
    nameSchemeHandler.setNameScheme(newNameScheme);
    Message msgChangeNameScheme;
    msgChangeNameScheme.type = Message::Type::controller_changeNameScheme_view;
    msgChangeNameScheme.data[0].i = newNameScheme;
    emit(sendMessage(msgChangeNameScheme));
}

void Controller::savePoster()
{
    if (!fileDownloader.fileExists())
    {
        if (fileDownloader.saveFileAsImage())
        {
            setStatusMessage(interfaceLanguageHandler.getTranslation(
                                 LanguageData::Translate::posterSaved),
                             MainWindow::StatusMessageType::success);
        }
        else
        {
            setStatusMessage(interfaceLanguageHandler.getTranslation(
                                 LanguageData::Translate::posterNotSaved),
                             MainWindow::StatusMessageType::error);
        }
    }
    else // Poster already exists
    {
        Message msgPosterAlreadyExists;
        msgPosterAlreadyExists.type = Message::Type::controller_posterAlreadyExists_view;
        emit(sendMessage(msgPosterAlreadyExists));
    }
}

void Controller::setDirectory(QString path)
{
    Message msgStartDirectoryLoading;
    msgStartDirectoryLoading.type = Message::Type::controller_startDirectoryLoading_view;
    emit(sendMessage(msgStartDirectoryLoading));
    emit(initializeDirectory(path));
}

void Controller::renameFiles()
{
    Message msgRenameStarted;
    msgRenameStarted.type = Message::Type::controller_renameStarted_view;
    emit(sendMessage(msgRenameStarted));

    directoryHandler->setEpisodeNames(*episodeNameHandler.getEpisodeNames());
    emit(rename());
}

void Controller::undoRenameFiles()
{
    Message msgRenameStarted;
    msgRenameStarted.type = Message::Type::controller_renameStarted_view;
    emit(sendMessage(msgRenameStarted));

    emit(undoRename());
}

void Controller::updateView()
{
    int amountSeasons = seriesData.getAmountSeasons();
    const auto episodeNames = episodeNameHandler.getEpisodeNames();
    const auto atLeastOneSideEmpty = episodeNameHandler.atLeastOneSideEmpty();

    Message msgViewUpdate;
    msgViewUpdate.type = Message::Type::controller_updateView_view;
    msgViewUpdate.data[0].i = amountSeasons;
    msgViewUpdate.data[1].episodeNamesPointer = episodeNames;
    msgViewUpdate.data[2].b = atLeastOneSideEmpty;
    emit(sendMessage(msgViewUpdate));
    updateRenameButtonAndSavePoster();
}

void Controller::updateRenameButtonAndSavePoster()
{
    QDir testDir("");

    bool directorySet = (seriesData.getWorkingDirectory().absolutePath() != testDir.absolutePath());
    bool seriesSet = !seriesData.getSeries().isEmpty();

    bool enableRenameButton = episodeNameHandler.atLeastOneEpisodeCanBeRenamed();
    bool enableSavePoster = seriesSet & directorySet & !seriesData.getPosterUrl().isEmpty();

    Message msgEnableRenameButton;
    msgEnableRenameButton.type = Message::Type::controller_enableRenameButton_view;
    msgEnableRenameButton.data[0].b = enableRenameButton;
    emit(sendMessage(msgEnableRenameButton));

    Message msgEnableSavePoster;
    msgEnableSavePoster.type = Message::Type::controller_enableSavePoster_view;
    msgEnableSavePoster.data[0].b = enableSavePoster;
    emit(sendMessage(msgEnableSavePoster));
}

void Controller::removeFileType(int index)
{
    fileTypeHandler.removeFileType(index);
    QStringList fileTypes = fileTypeHandler.getFileTypes();

    directoryHandler->setFileTypes(fileTypes);
    QDir directory = seriesData.getWorkingDirectory();
    setDirectory(directory.absolutePath());

    Message msgRemoveFileType;
    msgRemoveFileType.type = Message::Type::controller_removeFileType_settings;
    msgRemoveFileType.data[0].i = index;
    emit(sendMessage(msgRemoveFileType));

}

void Controller::notify(Message &msg)
{
    switch (msg.type)
    {
    case Message::Type::view_changeSeriesText_controller:
    {
        QString series = *msg.data[0].qsPointer;
        QString oldSeries = seriesParser.getSeriesInput();
        // Only load series on change
        if (series != oldSeries)
        {
            int season = 1;
            if (settings.getAutoSetDetectedSeason())
            {
                int foundSeason = directoryHandler->getFoundSeason();
                if (foundSeason > 0 && foundSeason <= 100)
                {
                    season = foundSeason;
                }
            }

            changeSeries(series, season);

            if (settings.getAutoSetDetectedSeason())
            {
                Message msgSetSeasonInView;
                msgSetSeasonInView.type = Message::Type::controller_setSeason_view;
                msgSetSeasonInView.data[0].i = season;
                emit(sendMessage(msgSetSeasonInView));
            }
        }
        break;
    }
    case Message::Type::view_changeSeason_controller:
    {
        int selectedSeason = msg.data[0].i;
        int oldSelectedSeason = seriesData.getSelectedSeason();
        // Only write on change
        if (selectedSeason != oldSelectedSeason)
            changeSeason(selectedSeason);
        break;
    }
    case Message::Type::view_changeSeriesLanguage_controller:
    {
        int languageIndex = msg.data[0].i;
        QString language = seriesLanguageHandler.getLanguageList().at(languageIndex);
        QString languageShortName = seriesLanguageHandler.getShortName(languageIndex + 1);
        QString oldLanguageShortName = seriesData.getSelectedLanguage();
        // Only write on change
        if (oldLanguageShortName != languageShortName)
            changeSeriesLanguage(language);
        break;
    }
    case Message::Type::view_changeDirectory_controller:
    {
        QString path = *msg.data[0].qsPointer;
        setDirectory(path);
        break;
    }
    case Message::Type::view_switchToDirectory_controller:
    {
        int level = msg.data[0].i;
        int selection = msg.data[1].i;
        QString path = directoryHandler->getDirectoryViaStructure(level, selection);
        setDirectory(path);
        break;
    }
    case Message::Type::view_updateDirectory_controller:
    {
        setDirectory(directoryHandler->getDirectoryPathInput());
        break;
    }
    case Message::Type::view_changeNewFileName_controller:
    {
        int row = msg.data[0].i;
        QString newFileName = *msg.data[1].qsPointer;

        episodeNameHandler.setNewName(newFileName, row);
        updateRenameButtonAndSavePoster();
        updateView();
        break;
    }
    case Message::Type::view_rename_controller:
    {
        int foundSeason = directoryHandler->getFoundSeason();
        int selectedSeason =  seriesData.getSelectedSeason();

        if (foundSeason == 0 || foundSeason == selectedSeason)
        {
            renameFiles();
        }
        else
        {
            Message msgSeasonMismatch;
            msgSeasonMismatch.type = Message::Type::controller_seasonMismatch_view;
            emit(sendMessage(msgSeasonMismatch));
        }
        break;
    }
    case Message::Type::view_forceRename_controller:
    {
        renameFiles();
        break;
    }
    case Message::Type::view_undoRenaming_controller:
    {
        undoRenameFiles();
        break;
    }
    case Message::Type::view_changeNameScheme_controller:
    {
        int selectedNameScheme = msg.data[0].i;
        changeNameScheme(selectedNameScheme);
        updateNewFileNames();
        updateView();
        break;
    }
    case Message::Type::settings_changeGUILanguage_controller:
    {
        QString language = *msg.data[0].qsPointer;
        changeInterfaceLanguage(language);
        break;
    }
    case Message::Type::view_savePoster_controller:
    {
        savePoster();
        break;
    }
    case Message::Type::view_forceSavePoster_conroller:
    {
        if (fileDownloader.saveFileAsImage(true))
            setStatusMessage(interfaceLanguageHandler.getTranslation(
                                 LanguageData::Translate::posterSaved),
                             MainWindow::StatusMessageType::success);
        else
            setStatusMessage(interfaceLanguageHandler.getTranslation(
                                 LanguageData::Translate::posterNotSaved),
                             MainWindow::StatusMessageType::error);
        break;
    }
    case Message::Type::view_setWindowRect_controller:
    {
        QRect windowRect = *msg.data[0].qRectPointer;
        settings.setWindowRect(windowRect);
        break;
    }
    case Message::Type::view_showAboutDialog_controller:
    {
        Message msgShowAboutDialog;
        msgShowAboutDialog.type = Message::Type::controller_showAboutDialog_about;
        emit(sendMessage(msgShowAboutDialog));
        break;
    }
    case Message::Type::view_showSettingsWindow_controller:
    {
        Message msgShowSettingsDialog;
        msgShowSettingsDialog.type = Message::Type::controller_showSettingsWindow_settings;
        emit(sendMessage(msgShowSettingsDialog));
        break;
    }
    case Message::Type::settings_changeSeriesParser_controller:
    {
        auto selectedSeriesParser = (SeriesParser::Parser)msg.data[0].i;
        changeSeriesParser(selectedSeriesParser);
        break;
    }
    case Message::Type::settings_saveSeries_controller:
    {
        bool saveSeries = msg.data[0].b;
        settings.setSaveSeries(saveSeries);
        break;
    }
    case Message::Type::settings_savePath_controller:
    {
        bool savePath = msg.data[0].b;
        settings.setSavePath(savePath);
        break;
    }
    case Message::Type::settings_savePoster_controller:
    {
        bool savePoster = msg.data[0].b;
        settings.setSavePosterInDirectory(savePoster);
        break;
    }
    case Message::Type::settings_setDetectedSeason_controller:
    {
        bool setDetectedSeason = msg.data[0].b;
        settings.setAutoSetDetectedSeason(setDetectedSeason);
        break;
    }
    case Message::Type::settings_reset_controller:
    {
        settings.resetSettingsFile();
        initializeSettings();
        break;
    }
    case Message::Type::settings_useDarkTheme_controller:
    {
        bool useDarkTheme = msg.data[0].b;
        settings.setDarkTheme(useDarkTheme);
        break;
    }
    case Message::Type::settings_showSeriesInfo_controller:
    {
        bool showSeriesInfo = msg.data[0].b;
        settings.setShowSeriesInfo(showSeriesInfo);

        if (showSeriesInfo)
            setSeriesInformation();

        Message msgShowSeriesInfo;
        msgShowSeriesInfo.type = Message::Type::controller_showSeriesInfo_view;
        msgShowSeriesInfo.data[0].b = showSeriesInfo;
        emit(sendMessage(msgShowSeriesInfo));

        break;
    }
    case Message::Type::settings_addNameScheme_controller:
    {
        QString nameScheme = *msg.data[0].qsPointer;
        int oldSelectedNameScheme = nameSchemeHandler.getSelectedNameSchemeIndex();

        nameSchemeHandler.addNameScheme(nameScheme);
        int lastIndex = nameSchemeHandler.getAmountNameSchemes() - 1;
        nameSchemeHandler.setNameScheme(lastIndex);
        QString nameSchemeRepresentation = nameSchemeHandler.getNameSchemeRepresentation();
        QString newNameScheme = nameSchemeHandler.getNameScheme();
        nameSchemeHandler.setNameScheme(oldSelectedNameScheme);

        Message msgAddNameSchemeView;
        msgAddNameSchemeView.type = Message::Type::controller_addNameScheme_view;
        msgAddNameSchemeView.data[0].qsPointer = &nameSchemeRepresentation;
        emit(sendMessage(msgAddNameSchemeView));

        Message msgAddRawNameSchemeSettings;
        msgAddRawNameSchemeSettings.type = Message::Type::controller_addRawNameScheme_settings;
        msgAddRawNameSchemeSettings.data[0].qsPointer = &newNameScheme;
        emit(sendMessage(msgAddRawNameSchemeSettings));

        break;
    }
    case Message::Type::settings_removeNameScheme_controller:
    {
        int indexToRemove = msg.data[0].i;
        nameSchemeHandler.removeNameScheme(indexToRemove);

        Message msgRemoveNameScheme;
        msgRemoveNameScheme.type = Message::Type::controller_removeNameScheme_view;
        msgRemoveNameScheme.data[0].i = indexToRemove;
        emit(sendMessage(msgRemoveNameScheme));

        break;
    }
    case Message::Type::settings_replaceNameScheme_controller:
    {
        int indexToChange = msg.data[0].i;
        QString newNameScheme = *msg.data[1].qsPointer;

        if (newNameScheme.isEmpty()) // Remove
        {
            nameSchemeHandler.removeNameScheme(indexToChange);

            Message msgRemoveNameScheme;
            msgRemoveNameScheme.type = Message::Type::controller_removeNameScheme_view;
            msgRemoveNameScheme.data[0].i = indexToChange;
            emit(sendMessage(msgRemoveNameScheme));
        }
        else // Replace
        {
            int oldSelectedNameSchemeIndex = nameSchemeHandler.getSelectedNameSchemeIndex();

            nameSchemeHandler.replaceNameScheme(indexToChange, newNameScheme);
            nameSchemeHandler.setNameScheme(indexToChange);
            QString newNameSchemeRepresentation = nameSchemeHandler.getNameSchemeRepresentation();
            nameSchemeHandler.setNameScheme(oldSelectedNameSchemeIndex);

            Message msgReplaceNameScheme;
            msgReplaceNameScheme.type = Message::Type::controller_replaceNameScheme_view;
            msgReplaceNameScheme.data[0].i = indexToChange;
            msgReplaceNameScheme.data[1].qsPointer = &newNameSchemeRepresentation;
            emit(sendMessage(msgReplaceNameScheme));

            if (oldSelectedNameSchemeIndex == indexToChange)
            {
                changeNameScheme(oldSelectedNameSchemeIndex);
                updateNewFileNames();
                updateView();
            }
        }
        break;
    }
    case Message::Type::settings_addFileType_controller:
    {
        QString fileType = *msg.data[0].qsPointer;
        int position = fileTypeHandler.addFileType(fileType);

        QStringList fileTypes = fileTypeHandler.getFileTypes();
        directoryHandler->setFileTypes(fileTypes);
        QDir directory = seriesData.getWorkingDirectory();
        setDirectory(directory.absolutePath());

        Message msgAddFileTypeSettings;
        msgAddFileTypeSettings.type = Message::Type::controller_addFileType_settings;
        msgAddFileTypeSettings.data[0].i = position;
        msgAddFileTypeSettings.data[1].qsListPointer = &fileTypes;
        emit(sendMessage(msgAddFileTypeSettings));

        break;
    }
    case Message::Type::settings_removeFileType_controller:
    {
        int indexToRemove = msg.data[0].i;
        removeFileType(indexToRemove);
        break;
    }
    case Message::Type::settings_replaceFileType_controller:
    {
        int indexToChange = msg.data[0].i;
        QString newNameScheme = *msg.data[1].qsPointer;

        if (newNameScheme.isEmpty()) // Remove
        {
            removeFileType(indexToChange);
        }
        else // Replace
        {
            int position = fileTypeHandler.setFileType(indexToChange, newNameScheme);
            QStringList fileTypes = fileTypeHandler.getFileTypes();

            Message msgChangeFileType;
            msgChangeFileType.type = Message::Type::controller_replaceFileType_settings;
            msgChangeFileType.data[0].i = position;
            msgChangeFileType.data[1].qsListPointer = &fileTypes;
            emit(sendMessage(msgChangeFileType));
        }
        break;
    }
    default:
        break;
    }
}

void Controller::directorySet(const bool &initialized)
{
    QString path = directoryHandler->getDirectoryPathInput();
    QDir newDirectory("");
    QStringList newOldFileNames;
    QStringList newSuffixes;
    Positions newPositions;

    // Update directory and file infos
    if (initialized)
    {
        newDirectory = QDir(path);
        newSuffixes = directoryHandler->getFilesSuffix();
        newOldFileNames = directoryHandler->getFilesWithoutSuffix();
        newPositions = directoryHandler->getFilePositions();

        fileDownloader.setFilePath(path, "poster.jpg");

        std::vector<QStringList> pathStructure = directoryHandler->getPathStructure();
        bool containsRoot = directoryHandler->getStructureContainsRoot();

        Message msgUpdateDirectoryWidget;
        msgUpdateDirectoryWidget.type = Message::Type::controller_updateDirectoryWidget_view;
        msgUpdateDirectoryWidget.data[0].qsListVectorPointer = &pathStructure;
        msgUpdateDirectoryWidget.data[1].b = containsRoot;
        msgUpdateDirectoryWidget.data[2].qsPointer = &path;
        emit(sendMessage(msgUpdateDirectoryWidget));
    }

    seriesData.setWorkingDirectory(newDirectory);
    episodeNameHandler.setOldNames(newOldFileNames);
    episodeNameHandler.setFileTypes(newSuffixes);
    episodeNameHandler.setPositionDetermination(newPositions);

    updateView();

    Message msgStopDirectoryLoading;
    msgStopDirectoryLoading.type = Message::Type::controller_stopDirectoryLoading_view;
    emit(sendMessage(msgStopDirectoryLoading));
}

void Controller::renameDone(const bool &success)
{
    if (settings.getSavePosterInDirectory())
    {
        savePoster();
    }

    if (success)
    {
        // Success message
        QString renameSuccessful = interfaceLanguageHandler.getTranslation(
                    LanguageData::Translate::renameSuccess);
        setStatusMessage(renameSuccessful, MainWindow::StatusMessageType::success);
    }
    else
    {
        // Failure message
        QString renameFailure = interfaceLanguageHandler.getTranslation(
                    LanguageData::Translate::renameFailed);
        setStatusMessage(renameFailure, MainWindow::StatusMessageType::error);
    }
    // Update undo action
    Message msgEnableUndoRenaming;
    msgEnableUndoRenaming.type = Message::Type::controller_enableUndoRenaming_view;
    msgEnableUndoRenaming.data[0].b = directoryHandler->isUndoPossible();
    emit(sendMessage(msgEnableUndoRenaming));

    setDirectory(directoryHandler->getDirectoryPathInput());

    Message msgRenameFinished;
    msgRenameFinished.type = Message::Type::controller_renameFinished_view;
    emit(sendMessage(msgRenameFinished));
}

void Controller::undoRenameDone(const bool &success)
{
    if (success)
    {
        // Success Message
        QString undoRenameSuccessful = interfaceLanguageHandler.getTranslation(
                    LanguageData::Translate::undoRenamingSuccessful);
        setStatusMessage(undoRenameSuccessful, MainWindow::StatusMessageType::success);
    } else
    {
        // Failure Message
        QString undoRenameFailure = interfaceLanguageHandler.getTranslation(
                    LanguageData::Translate::undoRenamingFailed);
        setStatusMessage(undoRenameFailure, MainWindow::StatusMessageType::error);
    }
    // Update undo action
    Message msgEnableUndoRenaming;
    msgEnableUndoRenaming.type = Message::Type::controller_enableUndoRenaming_view;
    msgEnableUndoRenaming.data[0].b = directoryHandler->isUndoPossible();
    emit(sendMessage(msgEnableUndoRenaming));

    setDirectory(directoryHandler->getDirectoryPathInput());

    Message msgRenameFinished;
    msgRenameFinished.type = Message::Type::controller_renameFinished_view;
    emit(sendMessage(msgRenameFinished));
}

void Controller::renameProgressUpdate(const int totalObjects, const int currentObject,
                                      const QString oldName, const QString newName)
{
    QString oldFileName = oldName;
    QString newFileName = newName;

    Message msgUpdateRenameProgress;
    msgUpdateRenameProgress.type = Message::Type::controller_updateRenameProgess_view;
    msgUpdateRenameProgress.data[0].i = totalObjects;
    msgUpdateRenameProgress.data[1].i = currentObject;
    msgUpdateRenameProgress.data[2].qsPointer = &oldFileName;
    msgUpdateRenameProgress.data[3].qsPointer = &newFileName;
    emit(sendMessage(msgUpdateRenameProgress));
}
