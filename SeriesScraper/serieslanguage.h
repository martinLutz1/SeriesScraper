#ifndef SERIESLANGUAGE_H
#define SERIESLANGUAGE_H

#include <QDir>
#include <QFile>
#include <QStringList>
#include "jsonloader.h"

class SeriesLanguage : public JsonLoader
{
public:
    SeriesLanguage();
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


#endif // SERIESLANGUAGE_H
