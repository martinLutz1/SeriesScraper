#ifndef FILERENAMER_H
#define FILERENAMER_H

#include "message.h"
#include <QStringList>
#include <QDir>
#include <vector>

class FileRenamer
{
public:
    FileRenamer();
    void setOldFileNames(QStringList oldfileNameList);
    void setNewFileNames(QStringList newFileNameList);
    void setDirectory(QDir directory);
    int getRenameAmount();
    QString getOldFileName(int index);
    QString getNewFileName(int index);
    bool rename(bool isUndo = false);
    bool renameFile(int index);
    void addToUndoQueue();
    bool isRenamePossible();
    bool isUndoPossible();
    bool prepareUndo();

private:
    QDir workingDirectory;
    QStringList oldFileNameList;
    QStringList newFileNameList;

    std::vector<QDir> workingDirectoryStack;
    std::vector<QStringList> oldFileNameListStack;
    std::vector<QStringList> newFileNameListStack;
};

#endif // FILERENAMER_H
