#ifndef NAMESCHEMEHANDLER_H
#define NAMESCHEMEHANDLER_H

#include "rawloader.h"
#include "nameschemeparser.h"
#include <QFile>

class NameSchemeHandler : public RawLoader
{
public:
    NameSchemeHandler();
    ~NameSchemeHandler();
    bool readNameSchemeFile();
    bool saveNameSchemeFile();
    bool addNameScheme(QString nameScheme);
    bool removeNameScheme(int index);
    bool replaceNameScheme(int index, QString newNameScheme);
    bool setNameScheme(int index);
    QString getNameScheme();
    // Only run if setNameScheme(index) returned true before
    QString getFileName(QString series, QString airDate, int season, int episode, QString episodeName);
    QStringList getFileNameList(QString series, QString airDate, int amountEpisodes, int season, QStringList episodeName);
    QString getNameSchemeRepresentation();

    int getAmountNameSchemes();
    int getSelectedNameSchemeIndex();

private:
    int selectedNameSchemeIndex;
    NameSchemeParser nameSchemeParser;
    QFile *nameSchemeFile;
};

#endif // NAMESCHEMEHANDLER_H
