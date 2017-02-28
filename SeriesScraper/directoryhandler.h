#ifndef DIRECTORYHANDLER_H
#define DIRECTORYHANDLER_H

#include <QObject>
#include <QThread>
#include "directoryparser.h"
#include "filerenamer.h"
#include <QDebug>

class DirectoryHandler : public QObject
{
    Q_OBJECT
    QThread workerThreadDirectory;
private:
    DirectoryParser directoryParser;
    FileRenamer fileRenamer;

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

    void setNewFileNames(QStringList newFileNameList);
    bool isUndoPossible();

public slots:
    void initializeDirectory(QString path);
    void rename();
    void undoRename();

signals:
    void directoryInitialized(const bool &);
    void renameDone(const bool &);
    void undoRenameDone(const bool &);
};

#endif // DIRECTORYHANDLER_H
