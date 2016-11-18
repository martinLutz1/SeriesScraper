#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include "directoryparser.h"
#include "omdbseriesparser.h"
#include "tmdbseriesparser.h"
#include "filerenamer.h"
#include "seriesdata.h"
#include "nameschemehandler.h"
#include "message.h"
#include "languagecontrol.h"
#include "serieslanguage.h"

class Controller : public QObject
{
    Q_OBJECT
private:
    OMDbSeriesParser seriesParser;
    TMDbSeriesParser tmdbSeriesParser;
    DirectoryParser directoryParser;
    SeriesData seriesData;
    FileRenamer fileRenamer;
    NameSchemeHandler nameSchemeHandler;
    LanguageControl languageControl;
    SeriesLanguage seriesLanguage;

    void initializeNameSchemes();
    void initializeSeriesLanguages();
    void initializeGUILanguages();
    void updateNewFileNames();
    void setStatusMessage(QString status);

public:
    explicit Controller(QObject *parent = 0);
    void initialize();
    bool setSeries(QString series, int season); // Set series if existing and set table
    bool changeSeason(int season);
    bool changeLanguage(QString language);
    bool setDirectory(QDir directory);
    bool renameFiles();
    void updateView();
    void updateRenameButton();

public slots:
    void notify(Message &msg);

signals:
    void sendMessage(Message &msg);
};

#endif // CONTROLLER_H
