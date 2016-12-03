#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include "directoryparser.h"
#include "seriesparser.h"
#include "filerenamer.h"
#include "seriesdata.h"
#include "nameschemehandler.h"
#include "message.h"
#include "languagecontrol.h"
#include "serieslanguage.h"
#include "settings.h"

class Controller : public QObject
{
    Q_OBJECT
private:
    SeriesParser seriesParser;
    DirectoryParser directoryParser;
    SeriesData seriesData;
    FileRenamer fileRenamer;
    NameSchemeHandler nameSchemeHandler;
    LanguageControl languageControl;
    SeriesLanguage seriesLanguage;
    Settings settings;

    void initializeNameSchemes();
    void initializeSeriesLanguages();
    void initializeGUILanguages();
    void initializeSettings();
    void updateNewFileNames();
    void setStatusMessage(QString status);

public:
    explicit Controller(QObject *parent = 0);
    ~Controller();
    void initialize();
    bool loadSeries(QString series, int season); // Set series if existing and set table
    bool changeSeason(int season);
    bool changeGuiLanguage(QString language);
    void changeSeriesLanguage(QString language);
    void changeSeriesParser(int seriesParser);
    void changeSeries(QString series, int season);
    void changeSaveSeries(bool saveSeries);
    void changeSavePath(bool savePath);
    void changeNameScheme(int nameScheme);
    bool setDirectory(QString path);
    bool renameFiles();
    void updateView();
    void updateRenameButton();

public slots:
    void notify(Message &msg);

signals:
    void sendMessage(Message &msg);
};

#endif // CONTROLLER_H
