#include "serieslanguage.h"

#include <QCoreApplication>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIODevice>
#include <QDebug>

SeriesLanguage::SeriesLanguage()
{
    applicationDirectory = QCoreApplication::applicationDirPath();
    seriesLanguageFile.setFileName(applicationDirectory.absoluteFilePath("serieslanguages.json"));
}

bool SeriesLanguage::loadSeriesLanguageFile()
{
    languageShortNameList.clear();
    seriesLanguageList.clear();

    bool loadingSuccessful = false;
    successReading = seriesLanguageFile.open(QIODevice::ReadOnly);
    if (!successReading) {
        return false;
    }

    QByteArray languageByteArray = seriesLanguageFile.readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(languageByteArray, &err);
    if(doc.isObject())
    {
        QJsonObject obj = doc.object();
        seriesLanguageList = obj.keys();
        for (int i = 0; i < seriesLanguageList.size(); i++) {
            languageShortNameList << obj.value(seriesLanguageList.at(i)).toString();
        }
        loadingSuccessful = true;
    }

    seriesLanguageFile.close();
    return loadingSuccessful;
}

QStringList SeriesLanguage::getLanguageList()
{
    return seriesLanguageList;
}

QString SeriesLanguage::getShortName(QString language)
{
    for (int i = 0; i < seriesLanguageList.size(); i++) {
        if (seriesLanguageList.at(i) == language) {
            return languageShortNameList.at(i);
        }
    }
    // Not found, return default
    return defaulEntry;
}

QString SeriesLanguage::getShortName(int language)
{
    if (language >= 1) {
        return languageShortNameList.at(language - 1);
    }
    // Not found, return default
    else {
        return defaulEntry;
    }

}
