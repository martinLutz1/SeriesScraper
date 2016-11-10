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

    void initializeNameSchemes();
    void applyNameSchemes();
    void updateNewFileNames();

public:
    explicit Controller(QObject *parent = 0);
    void initialize();
    bool setSeries(QString series, int season); // Set series if existing and set table
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
