#ifndef DIRECTORYPARSER_H
#define DIRECTORYPARSER_H

#include <QDir>
#include <QStringList>
#include <iostream>

class DirectoryParser
{
private:
    QDir directory;
public:
    DirectoryParser();
    bool setDirectory(QDir directory);
    QStringList getFiles();
};

#endif // DIRECTORYPARSER_H
