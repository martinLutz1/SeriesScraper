#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include "directoryparser.h"
#include "seriesparser.h"
#include "filerenamer.h"
#include "seriesdata.h"
#include "message.h"
#include <QTimer>

class Controller : public QObject
{
    Q_OBJECT
private:
    QTimer *seriesLoadedTimer;
    SeriesParser seriesParser;
    DirectoryParser directoryParser;
    SeriesData seriesData;
    FileRenamer fileRenamer;

public:
    explicit Controller(QObject *parent = 0);
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
