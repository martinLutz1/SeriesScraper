#include "serieslanguagehandler.h"
#include <QCoreApplication>
#include <QByteArray>
#include <QJsonObject>
#include <QIODevice>
#include <QDebug>

SeriesLanguageHandler::SeriesLanguageHandler()
{
    applicationDirectory = QCoreApplication::applicationDirPath();
    filePath = applicationDirectory.absoluteFilePath("serieslanguages.json");
}

bool SeriesLanguageHandler::loadSeriesLanguageFile()
{
    languageShortNameList.clear();
    seriesLanguageList.clear();
    bool loadingSuccessful = loadJsonObject(filePath);

    if (loadingSuccessful)
    {
        seriesLanguageList = loadedObject.keys();
        for (int i = 0; i < seriesLanguageList.size(); i++)
            languageShortNameList << loadedObject.value(seriesLanguageList.at(i)).toString();
    }
    return loadingSuccessful;
}

QStringList SeriesLanguageHandler::getLanguageList()
{
    return seriesLanguageList;
}

QString SeriesLanguageHandler::getShortName(QString language)
{
    for (int i = 0; i < seriesLanguageList.size(); i++)
    {
        if (seriesLanguageList.at(i) == language)
            return languageShortNameList.at(i);
    }
    // Not found, return default
    return defaulEntry;
}

QString SeriesLanguageHandler::getShortName(int language)
{
    if (language > 0 && language <= languageShortNameList.size())
        return languageShortNameList.at(language - 1);
    else // Not found, return default
        return defaulEntry;
}
