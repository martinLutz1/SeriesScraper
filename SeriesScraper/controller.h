#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "message.h"
#include "settings.h"
#include "directoryparser.h"
#include "seriesparser.h"
#include "seriesdata.h"
#include "filerenamer.h"
#include "serieslanguagehandler.h"
#include "nameschemehandler.h"
#include "interfacelanguagehandler.h"
#include "filetypehandler.h"
#include "filedownloader.h"
#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
private:
    SeriesParser seriesParser;
    SeriesData seriesData;
    DirectoryParser directoryParser;
    FileRenamer fileRenamer;
    NameSchemeHandler nameSchemeHandler;
    FileTypeHandler fileTypeHandler;
    SeriesLanguageHandler seriesLanguageHandler;
    InterfaceLanguageHandler interfaceLanguageHandler;
    FileDownloader fileDownloader;
    Settings settings;

    void initializeFileTypes();
    void initializeNameSchemes();
    void initializeSeriesLanguages();
    void initializeInterfaceLanguages();
    void initializeSettings();
    void updateNewFileNames();
    void setStatusMessage(QString status, int type);
    void setSeriesInformation();

    bool loadSeries(QString series, int season);
    bool changeSeason(int season);
    bool changeInterfaceLanguage(QString language);
    void changeSeriesLanguage(QString language);
    void changeSeriesParser(int seriesParser);
    void changeSeries(QString series, int season);
    void changeSaveSeries(bool saveSeries);
    void changeSavePath(bool savePath);
    void changeNameScheme(int nameScheme);
    void savePoster();
    bool setDirectory(QString path);
    bool renameFiles();
    bool undoRenameFiles();
    void updateView();
    void updateRenameButtonAndSavePoster();
    void removeFileType(int index);

public:
    explicit Controller(QObject *parent = 0);
    ~Controller();
    void initialize();

public slots:
    void notify(Message &msg);

signals:
    void sendMessage(Message &msg);
};

#endif // CONTROLLER_H
