#ifndef DIRECTORYHANDLER_H
#define DIRECTORYHANDLER_H

#include <QObject>
#include <QThread>
#include <QDebug>

#include "directoryparser.h"
#include "filerenamer.h"
#include "episodenamehandler.h"
#include "episodename.h"

class DirectoryHandler : public QObject
{
    Q_OBJECT
    QThread workerThreadDirectory;
private:
    DirectoryParser directoryParser;
    FileRenamer fileRenamer;
    bool renameFiles(bool isUndo = false);

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
    Positions getFilePositions();

    void setEpisodeNames(EpisodeNames episodeNames);
    bool isUndoPossible();

public slots:
    void initializeDirectory(QString path);
    void rename();
    void undoRename();

signals:
    void directoryInitialized(const bool &);
    void renameDone(const bool &);
    void undoRenameDone(const bool &);
    void updateRenameProgress(const int &, const int &, const QString &, const QString &);
};

#endif // DIRECTORYHANDLER_H
