#ifndef SERIESLANGUAGE_H
#define SERIESLANGUAGE_H

#include <QDir>
#include <QFile>
#include <QStringList>

class SeriesLanguage
{
public:
    SeriesLanguage();
    bool loadSeriesLanguageFile();
    QStringList getLanguageList();
    QString getShortName(QString language);

private:
    bool successReading;
    QDir applicationDirectory;
    QFile seriesLanguageFile;

    QStringList seriesLanguageList;
    QStringList languageShortNameList;
};


#endif // SERIESLANGUAGE_H
