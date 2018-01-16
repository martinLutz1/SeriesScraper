#ifndef SERIESLANGUAGEHANDLER_H
#define SERIESLANGUAGEHANDLER_H

#include "jsonloader.h"
#include <QStringList>
#include <QFile>
#include <QDir>

class SeriesLanguageHandler : public JsonLoader
{
public:
    SeriesLanguageHandler();
    bool loadSeriesLanguageFile();
    QStringList getLanguageList();
    QString getShortName(QString language);
    QString getShortName(int language);

private:
    QDir applicationDirectory;
    QString filePath;
    QString defaulEntry = "en-EN";
    QStringList seriesLanguageList;
    QStringList languageShortNameList;
};


#endif // SERIESLANGUAGEHA NDLER_H
