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
    bool saveNameSchemeFile();
    bool addNameScheme(QString nameScheme);
    bool removeNameScheme(int index);
    bool replaceNameScheme(int index, QString newNameScheme);
    bool setNameScheme(int index);
    QString getNameScheme();
    // Only run if setNameScheme(index) returned true before
    QString getFileName(QString series, int season, int episode, QString episodeName);
    QStringList getFileNameList(QString series, int amountEpisodes, int season, QStringList episodeName);
    QString getNameSchemeRepresentation();

    int getAmountNameSchemes();
    int getSelectedNameSchemeIndex();

private:
    int selectedNameSchemeIndex;
    bool successReading;
    QStringList nameSchemeList;
    QDir applicationDirectory;
    QFile nameSchemeFile;
    NameSchemeParser nameSchemeParser;
};

#endif // NAMESCHEMEHANDLER_H
