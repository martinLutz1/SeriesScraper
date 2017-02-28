#ifndef FILERENAMER_H
#define FILERENAMER_H

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
    bool rename(bool isUndo = false);
    bool isUndoPossible();
    bool undo();

private:
    QDir workingDirectory;
    QStringList oldFileNameList;
    QStringList newFileNameList;

    std::vector<QDir> workingDirectoryStack;
    std::vector<QStringList> oldFileNameListStack;
    std::vector<QStringList> newFileNameListStack;
};

#endif // FILERENAMER_H
