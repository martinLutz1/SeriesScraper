#ifndef FILERENAMER_H
#define FILERENAMER_H

#include <QStringList>
#include <QDir>


class FileRenamer
{
public:
    FileRenamer();
    void setOldFileNames(QStringList oldfileNameList);
    void setNewFileNames(QStringList newFileNameList);
    void setDirectory(QDir directory);
    bool rename();
    bool isUndoPossible();
    bool deleteLastUndo();
    bool undo();

private:
    QStringList oldFileNameList;
    QStringList newFileNameList;
    QDir workingDirectory;

    bool undoPossible = false;
};

#endif // FILERENAMER_H
