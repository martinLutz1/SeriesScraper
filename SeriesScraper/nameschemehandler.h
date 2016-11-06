#ifndef NAMESCHEMEHANDLER_H
#define NAMESCHEMEHANDLER_H

#include <QStringList>
#include <QDir>
#include "nameschemeparser.h"

class NameSchemeHandler
{
public:
    NameSchemeHandler();
    bool readNameSchemeFile();

    bool addNameScheme(QString nameScheme);
    bool removeNameScheme(int index);
    QString getNameScheme(int index);
    bool setNameScheme(int index);
    // Only run if setNameScheme(index) returned true before
    QString getFileName(QString series, int season, int episode, QString episodeName);
    QStringList getFileNameList(QString series, int amountEpisodes, int season, QStringList episodeName);
    QString getNameSchemeRepresentation();

    int getAmountNameSchemes();

private:
    bool successReading;
    QStringList nameSchemeList;
    QDir applicationDirectory;
    QFile nameSchemeFile;
    NameSchemeParser nameSchemeParser;
};

#endif // NAMESCHEMEHANDLER_H
