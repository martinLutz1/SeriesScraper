#include "controller.h"
#include <QDebug>
#include <vector>

void Controller::initializeNameSchemes()
{
    bool fileRead = nameSchemeHandler.readNameSchemeFile();
    // Add default entry if name scheme list not found
    if (!fileRead) {
        nameSchemeHandler.addNameScheme("%$series% - S%$season%E%$episode(2)% - %$episodeName%");
        nameSchemeHandler.setNameScheme(0);
        QString nameSchemeRepresentation = nameSchemeHandler.getNameSchemeRepresentation();

        Message msgAddNameScheme;
        msgAddNameScheme.type = Message::controller_addNameScheme_view;
        msgAddNameScheme.data[0].qsPointer = &nameSchemeRepresentation;
        emit(sendMessage(msgAddNameScheme));

        QString nameSchemeNotFound = languageControl.getTranslation(LanguageData::nameSchemeNotFound);
        qDebug() << nameSchemeNotFound;
        setStatusMessage(nameSchemeNotFound);
        return;
    }

    int amountNameSchemes = nameSchemeHandler.getAmountNameSchemes();
    // Read all name schemes
    for (int i = 0; i < amountNameSchemes; i++) {
        nameSchemeHandler.setNameScheme(i);
        QString nameSchemeRepresentation = nameSchemeHandler.getNameSchemeRepresentation();

        Message msgAddNameScheme;
        msgAddNameScheme.type = Message::controller_addNameScheme_view;
        msgAddNameScheme.data[0].qsPointer = &nameSchemeRepresentation;
        emit(sendMessage(msgAddNameScheme));
    }
    nameSchemeHandler.setNameScheme(0);
}

void Controller::initializeSeriesLanguages()
{
    bool fileRead = seriesLanguage.loadSeriesLanguageFile();
    QString *english = new QString("English");

    // Add default entry if series language file not found
    if (!fileRead) {
        QString languageFileReadingFailure = languageControl.getTranslation(LanguageData::seriesLanguageNotFound);
        setStatusMessage(languageFileReadingFailure);

        Message msgAddSeriesLanguage;
        msgAddSeriesLanguage.type = Message::controller_addSeriesLanguage_view;
        msgAddSeriesLanguage.data[0].qsPointer = english;
        emit(sendMessage(msgAddSeriesLanguage));
    }
    else {
        QStringList seriesLanguages = seriesLanguage.getLanguageList();

        for (int i = 0; i < seriesLanguages.size(); i++) {
            QString language = seriesLanguages.at(i);
            Message msgAddSeriesLanguage;
            msgAddSeriesLanguage.type = Message::controller_addSeriesLanguage_view;
            msgAddSeriesLanguage.data[0].qsPointer = &language;
            emit(sendMessage(msgAddSeriesLanguage));
        }
    }
    QString languageShortName = seriesLanguage.getShortName(*english);
    seriesData.setLanguage(languageShortName);
    delete english;
}

void Controller::updateNewFileNames()
{
    QString series = seriesData.getSeries();
    int season = seriesData.getSelectedSeason();
    int amountEpisodes = seriesData.getAmountEpisodes();
    QStringList episodeList = seriesData.getEpisodes();

    QStringList newFileNames = nameSchemeHandler.getFileNameList(series, season, amountEpisodes, episodeList);
    seriesData.setNewFileNames(newFileNames);
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

void Controller::initialize()
{
    bool languageInitSuccess = languageControl.initialize();
    if (languageInitSuccess) {
        languageControl.loadLanguage("English");
    }
    else {
        setStatusMessage("No language files found");
        // Disable language selection
    }
    initializeNameSchemes();
    initializeSeriesLanguages();
}

bool Controller::setSeries(QString series, int season)
{
    Message msgStartLoading;
    msgStartLoading.type = Message::controller_startSeriesLoading_view;
    emit(sendMessage(msgStartLoading));
    // bool seriesFound = seriesParser.getSeriesSeason("http://www.omdbapi.com/?", series, season, "Title");
    bool seriesFound = tmdbSeriesParser.scrapeSeries(series);
    if (seriesFound) {
        int amountSeasons = tmdbSeriesParser.getAmountSeasons();
        QString seriesName = tmdbSeriesParser.getSeriesName();
        QString language = seriesData.getLanguage();
        QStringList episodeList = tmdbSeriesParser.getSeason(season, language); // Make language selection available
        // QStringList episodeList = seriesParser.getIDValue();
        // int amountSeasons = seriesParser.getAmountSeasons();
        seriesData.setSeries(seriesName);
        seriesData.setSelectedSeason(season);
        seriesData.setEpisodes(episodeList);
        seriesData.setAmountSeasons(amountSeasons);
        updateNewFileNames();

        updateView();

        Message msgSuccessLoading;
        msgSuccessLoading.type = Message::controller_successSeriesLoading_view;
        emit(sendMessage(msgSuccessLoading));
        return true;
    }
    else { // Didnt find series
        seriesData.setSeries("");
        seriesData.setSelectedSeason(0);
        seriesData.setEpisodes(QStringList());
        seriesData.setAmountSeasons(0);

        Message msgFailureLoading;
        msgFailureLoading.type = Message::controller_failureSeriesLoading_view;
        emit(sendMessage(msgFailureLoading));

        return false;
    }
}

bool Controller::changeSeason(int season)
{
    Message msgStartLoading;
    msgStartLoading.type = Message::controller_startSeriesLoading_view;
    emit(sendMessage(msgStartLoading));

    QString language = seriesData.getLanguage();
    QStringList episodeList = tmdbSeriesParser.getSeason(season, language);

    seriesData.setSelectedSeason(season);
    seriesData.setEpisodes(episodeList);
    updateNewFileNames();
    updateView();

    if (episodeList.isEmpty()) {
        Message msgFailureLoading;
        msgFailureLoading.type = Message::controller_failureSeriesLoading_view;
        emit(sendMessage(msgFailureLoading));
        return false;
    }
    else {
        Message msgSuccessLoading;
        msgSuccessLoading.type = Message::controller_successSeriesLoading_view;
        emit(sendMessage(msgSuccessLoading));
        return true;
    }
}

bool Controller::changeLanguage(QString language)
{
    Message msgStartLoading;
    msgStartLoading.type = Message::controller_startSeriesLoading_view;
    emit(sendMessage(msgStartLoading));

    int season = seriesData.getSelectedSeason();
    QStringList episodeList = tmdbSeriesParser.getSeason(season, language);

    seriesData.setLanguage(language);
    seriesData.setEpisodes(episodeList);
    updateNewFileNames();
    updateView();

    if (episodeList.isEmpty()) {
        Message msgFailureLoading;
        msgFailureLoading.type = Message::controller_failureSeriesLoading_view;
        emit(sendMessage(msgFailureLoading));
        return false;
    }
    else {
        Message msgSuccessLoading;
        msgSuccessLoading.type = Message::controller_successSeriesLoading_view;
        emit(sendMessage(msgSuccessLoading));
        return true;
    }
}

bool Controller::setDirectory(QDir directory)
{
    bool directoryExists = directoryParser.initializeDirectory(directory);
    if (directoryExists) {
        seriesData.setWorkingDirectory(directory);

        QStringList suffixesList = directoryParser.getFilesSuffix();
        seriesData.setSuffixes(suffixesList);

        QStringList oldFileNames = directoryParser.getOldFileNameList();
        seriesData.setOldFileNames(oldFileNames);
        updateView();

        return true;
    }
    else {
        QDir testDir("");
        seriesData.setWorkingDirectory(testDir);
        return false;
    }
}

bool Controller::renameFiles()
{
    QDir directory = seriesData.getWorkingDirectory();
    QStringList newFileNameList = seriesData.getNewFileNames();
    QStringList oldFileNameList = seriesData.getOldFileNames();
    QStringList suffixesList = seriesData.getSuffixes();

    fileRenamer.setDirectory(directory);
    fileRenamer.setOldFileNames(oldFileNameList);
    fileRenamer.setNewFileNames(newFileNameList);
    fileRenamer.setSuffixes(suffixesList);

    if (fileRenamer.rename())
    {
        QStringList renamedFiles = directoryParser.getOldFileNameList();
        seriesData.setOldFileNames(renamedFiles);
        updateView();

        // Feedback
        QString renameSuccessful = languageControl.getTranslation(LanguageData::renameSuccess);
        setStatusMessage(renameSuccessful);
        return true;

    } else
    {
        // Feedback
        QString renameFailure = languageControl.getTranslation(LanguageData::renameFailed);
        setStatusMessage(renameFailure);
        return false;

    }
}

void Controller::updateView()
{
    QStringList newFileNameList = seriesData.getNewFileNames();
    QStringList oldFileNameList = seriesData.getOldFileNamesForView();
    // Operate on suffixes
    int amountSeasons = seriesData.getAmountSeasons();

    Message msgViewUpdate;
    msgViewUpdate.type = Message::controller_updateView_view;
    msgViewUpdate.data[0].i = amountSeasons;
    msgViewUpdate.data[1].qsListPointer = &oldFileNameList;
    msgViewUpdate.data[2].qsListPointer = &newFileNameList;
    emit(sendMessage(msgViewUpdate));
}

void Controller::updateRenameButton()
{
    // Check wether the directory is the root dir of the program (-> not changed)
    QDir testDir("");
    bool directorySet = (seriesData.getWorkingDirectory().absolutePath() != testDir.absolutePath());
    bool seriesSet = !seriesData.getSeries().isEmpty();
    bool enableButton = seriesSet & directorySet;

    Message msgEnableButton;
    msgEnableButton.type = Message::controller_enableButton_view;
    msgEnableButton.data[0].b = enableButton;
    emit(sendMessage(msgEnableButton));
}

void Controller::notify(Message &msg)
{
    switch (msg.type) {
    case Message::view_seriesText_changed_controller:
    {
        QString seriesText = *msg.data[0].qsPointer;
        int season = msg.data[1].i;
        bool seriesSet = setSeries(seriesText, season);
        bool isEmpty = seriesText.isEmpty();

        // Emit wether series was scraped succesfully
        Message msgSeriesSet;
        msgSeriesSet.type = Message::controller_seriesSet_view;
        msgSeriesSet.data[0].b = seriesSet;
        msgSeriesSet.data[1].b = isEmpty;
        emit(sendMessage(msgSeriesSet));

        updateRenameButton();
        break;
    }
    case Message::view_season_changed_controller:
    {
        int selectedSeason = msg.data[0].i;
        int oldSelectedSeason = seriesData.getSelectedSeason();
        // Only write on change
        if (selectedSeason != oldSelectedSeason) {
            changeSeason(selectedSeason);
        }
        break;
    }
    case Message::view_directory_changed_controller:
    {
        QString directory = *msg.data[0].qsPointer;
        bool directorySet = setDirectory(QDir(directory));
        if (directorySet) {
            updateView();
            updateRenameButton();
        }

        break;
    }
    case Message::view_rename_controller:
    {
        renameFiles();
        break;
    }
    case Message::view_changeNameScheme_controller:
    {
        int selectedNameScheme = msg.data[0].i;
        nameSchemeHandler.setNameScheme(selectedNameScheme);
        updateNewFileNames();
        updateView();
        break;
    }
    case Message::view_changeGUILanguage_controller:
    {
        QString language = *msg.data[0].qsPointer;
        bool loadingSuccessful = languageControl.loadLanguage(language);

        if (loadingSuccessful) {
            QStringList translationList = languageControl.getTranslationList();

            // Send translations to view, about and settings
            Message msgChangeLocalization;
            msgChangeLocalization.type = Message::controller_changeLocalization_view;
            msgChangeLocalization.data[0].qsListPointer = &translationList;
            emit(sendMessage(msgChangeLocalization));
        }
        else {
            setStatusMessage("Could not read language file " + language + ".json");
        }
        break;
    }
    case Message::view_changeSeriesLanguage_controller:
    {
        int languageIndex = msg.data[0].i;
        QString language = seriesLanguage.getShortName(languageIndex + 1);
        QString oldLanguage = seriesData.getLanguage();
        // Only write on change
        if (oldLanguage != language)  {
            seriesData.setLanguage(language);
            // Only load season if series set
            if (!seriesData.getSeries().isEmpty()) {
                changeLanguage(language);
            }
        }
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
    default:
        break;
    }
}
