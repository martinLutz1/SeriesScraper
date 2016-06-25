#ifndef DIRECTORYPARSER_H
#define DIRECTORYPARSER_H

#include <QDir>
#include <QStringList>
#include <QRegularExpression>

class DirectoryParser
{
private:
    QDir directory;
    QStringList loadedFiles;
    QRegularExpression episodeNumberExpression;

    void setNameFilterToAll();
public:
    DirectoryParser();
    bool setDirectory(QDir directory);
    QStringList getFiles();
    QStringList getFiles(QString extension);
};

#endif // DIRECTORYPARSER_H
