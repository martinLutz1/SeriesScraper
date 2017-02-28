#ifndef DIRECTORYHANDLER_H
#define DIRECTORYHANDLER_H

#include <QObject>
#include <QThread>
#include "directoryparser.h"
#include "filerenamer.h"

class DirectoryHandler : public QObject
{
    Q_OBJECT
    QThread workerThread;
private:
    DirectoryParser directoryParser;

public:
    explicit DirectoryHandler(QObject *parent = 0);
    void setFileTypes(QStringList fileTypes);
    std::vector<QStringList> getPathStructure();
    QString getDirectoryViaStructure(int level, int selection);
    bool getStructureContainsRoot();
    QString getDirectoryPathInput();
    int getFoundSeason();
    QStringList getFiles();
    QStringList getFilesWithoutSuffix();
    QStringList getFilesSuffix();


public slots:
    void initializeDirectory(QString path);

signals:
    void directoryInitialized(const bool &);
};

#endif // DIRECTORYHANDLER_H
