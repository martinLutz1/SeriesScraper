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

private:
    QStringList oldFileNameList;
    QStringList newFileNameList;
    QDir workingDirectory;
};

#endif // FILERENAMER_H
