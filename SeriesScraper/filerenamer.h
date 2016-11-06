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
    void setSuffixes(QStringList suffixList);
    bool rename();

private:
    QStringList suffixes;
    QStringList oldFileNameList;
    QStringList newFileNameList;
    QDir workingDirectory;
};

#endif // FILERENAMER_H
