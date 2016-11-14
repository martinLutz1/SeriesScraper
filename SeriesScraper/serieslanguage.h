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
    QString getShortName(int language);

private:
    bool successReading;
    QDir applicationDirectory;
    QFile seriesLanguageFile;

    QString defaulEntry = "en-EN";
    QStringList seriesLanguageList;
    QStringList languageShortNameList;
};


#endif // SERIESLANGUAGE_H
