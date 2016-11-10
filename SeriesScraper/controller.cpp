#include "controller.h"
#include <QDebug>
#include <vector>

void Controller::initializeNameSchemes()
{
    bool fileRead = nameSchemeHandler.readNameSchemeFile();
    // Add default entry if name scheme list not found
    if (!fileRead) {
        nameSchemeHandler.addNameScheme("%$series% s%$season%e%$episode(2)% - %$episodeName%");
        nameSchemeHandler.setNameScheme(0);
        QString nameSchemeRepresentation = nameSchemeHandler.getNameSchemeRepresentation();

        Message msgAddNameScheme;
        msgAddNameScheme.type = Message::controller_addNameScheme_view;
        msgAddNameScheme.data[0].qsPointer = &nameSchemeRepresentation;
        emit(sendMessage(msgAddNameScheme));
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

void Controller::applyNameSchemes()
{
    int amountEpisodes = seriesData.getAmountEpisodes();
    //seriesData.set
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

Controller::Controller(QObject *parent) : QObject(parent)
{
}

void Controller::initialize()
{
    initializeNameSchemes();
}

bool Controller::setSeries(QString series, int season)
{
    Message msgStartLoading;
    msgStartLoading.type = Message::controller_startSeriesLoading_view;
    emit(sendMessage(msgStartLoading));

    bool seriesFound = seriesParser.getSeriesSeason("http://www.omdbapi.com/?", series, season, "Title");
    if (seriesFound) {
        QStringList episodeList = seriesParser.getIDValue();
        int amountSeasons = seriesParser.getAmountSeasons();

        seriesData.setSeries(series);
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
        return true;
        // Output!
    } else
    {
        false;
        // Output!
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
        QString series = seriesData.getSeries();
        bool seriesSet = setSeries(series, selectedSeason);
        bool isEmpty = series.isEmpty();

        // Emit wether series was scraped succesfully
        Message msgSeriesSet;
        msgSeriesSet.type = Message::controller_seriesSet_view;
        msgSeriesSet.data[0].b = seriesSet;
        msgSeriesSet.data[1].b = isEmpty;
        emit(sendMessage(msgSeriesSet));

        break;
    }
    case Message::view_directory_changed_controller:
    {
        QString directory = *msg.data[0].qsPointer;
        bool directorySet = setDirectory(QDir(directory));
        updateView();
        updateRenameButton();

        break;
    }
    case Message::view_rename_controller:
    {
        renameFiles(); // Bool, operate on Output!
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
    case Message::view_changeLanguage_controller:
    {
        QString language = *msg.data[0].qsPointer;
        bool loadingSuccessful = languageControl.loadLanguage(language);

        if (loadingSuccessful) {
            QStringList translationList = languageControl.getTranslationList();

            // Send translations to view
            Message msgChangeLocalization;
            msgChangeLocalization.type = Message::controller_changeLocalization_view;
            msgChangeLocalization.data[0].qsListPointer = &translationList;
            emit(sendMessage(msgChangeLocalization));
        }
        else {
            // Give output
        }
        break;
    }
    default:
        break;
    }
}
