#include "settings.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

Settings::Settings()
{
    settingsFile.setFileName(QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("settings.json"));
    savePath = defaultSavePath;
    saveSeries = defaultSaveSeries;
    useDarkTheme = defaultUseDarkTheme;
    showSeriesInfo = defaultShowSeriesInfo;
    path = defaultPath;
    series = defaultSeries;
    season = defaultSeason;
    seriesDatabase = defaultSeriesDatabase;
    nameScheme = defaultNameScheme;
    guiLanguage = defaultGuiLanguage;
    seriesLanguage = defaultSeriesLanguage;
}

bool Settings::loadSettingsFile()
{
    bool loadingSuccessful = loadJsonObject(settingsFile.fileName());
    if (loadingSuccessful)
    {
        setSavePath(loadedObject.find(jsonKeySavePath).value().toBool());
        setSaveSeries(loadedObject.find(jsonKeySaveSeries).value().toBool());
        setDarkTheme(loadedObject.find(jsonKeyDarkTheme).value().toBool());
        setShowSeriesInfo(loadedObject.find(jsonKeyShowSeriesInfo).value().toBool());
        setPath(loadedObject.find(jsonKeyPath).value().toString());
        setSeries(loadedObject.find(jsonKeySeries).value().toString());
        setSeason(loadedObject.find(jsonKeySeason).value().toInt());
        setSeriesDatabase(loadedObject.find(jsonKeySeriesDatabase).value().toInt());
        setNameScheme(loadedObject.find(jsonKeyNameScheme).value().toInt());
        setGuiLanguage(loadedObject.find(jsonKeyGUILanguage).value().toString());
        setSeriesLanguage(loadedObject.find(jsonKeySeriesLanguage).value().toString());
    } else
        saveSettingsFile(); // Creates settings file with default values defined in constructor

    return loadingSuccessful;
}

bool Settings::saveSettingsFile()
{
    QJsonObject jsonSettings;
    jsonSettings.insert(jsonKeySavePath, savePath);
    jsonSettings.insert(jsonKeyPath, path);
    jsonSettings.insert(jsonKeyDarkTheme, useDarkTheme);
    jsonSettings.insert(jsonKeyShowSeriesInfo, showSeriesInfo);
    jsonSettings.insert(jsonKeySaveSeries, saveSeries);
    jsonSettings.insert(jsonKeySeries, series);
    jsonSettings.insert(jsonKeySeriesDatabase, seriesDatabase);
    jsonSettings.insert(jsonKeyGUILanguage, guiLanguage);
    jsonSettings.insert(jsonKeySeriesLanguage, seriesLanguage);
    jsonSettings.insert(jsonKeyNameScheme, nameScheme);
    jsonSettings.insert(jsonKeySeason, season);

    bool successReading = settingsFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    if (successReading)
        settingsFile.write(QJsonDocument(jsonSettings).toJson());
    settingsFile.close();

    return successReading;
}

bool Settings::resetSettingsFile()
{
    savePath = defaultSavePath;
    saveSeries = defaultSaveSeries;
    useDarkTheme = defaultUseDarkTheme;
    showSeriesInfo = defaultShowSeriesInfo;
    path = defaultPath;
    series = defaultSeries;
    season = defaultSeason;
    seriesDatabase = defaultSeriesDatabase;
    nameScheme = defaultNameScheme;
    guiLanguage = defaultGuiLanguage;
    seriesLanguage = defaultSeriesLanguage;
    return saveSettingsFile();
}

void Settings::setSavePath(bool savePathOnExit)
{
    savePath = savePathOnExit;
}

void Settings::setSaveSeries(bool saveSeriesOnExit)
{
    saveSeries = saveSeriesOnExit;
}

void Settings::setDarkTheme(bool useDarkTheme)
{
    this->useDarkTheme = useDarkTheme;
}

void Settings::setShowSeriesInfo(bool showSeriesInfo)
{
    this->showSeriesInfo = showSeriesInfo;
}

void Settings::setPath(QString path)
{
    this->path = path;
}

void Settings::setSeries(QString series)
{
    this->series = series;
}

void Settings::setSeason(int season)
{
    this->season = season;
}

void Settings::setSeriesDatabase(int seriesDatabase)
{
    if (seriesDatabase >= 0 && seriesDatabase <= 1)
        this->seriesDatabase = seriesDatabase;
    else // Set to default if seriesDatabase is not valid
        this->seriesDatabase = 0;
}

void Settings::setNameScheme(int nameScheme)
{
    this->nameScheme = nameScheme;
}

void Settings::setGuiLanguage(QString guiLanguage)
{
    this->guiLanguage = guiLanguage;
}

void Settings::setSeriesLanguage(QString seriesLanguage)
{
    this->seriesLanguage = seriesLanguage;
}

bool Settings::getSavePath()
{
    return savePath;
}

bool Settings::getSaveSeries()
{
    return saveSeries;
}

bool Settings::getDarkTheme()
{
    return useDarkTheme;
}

bool Settings::getShowSeriesInfo()
{
    return showSeriesInfo;
}

QString Settings::getSeries()
{
    return series;
}

QString Settings::getPath()
{
    return path;
}

QString Settings::getGuiLanguage()
{
    return guiLanguage;
}

QString Settings::getSeriesLanguage()
{
    return seriesLanguage;
}

int Settings::getSeason()
{
    return season;
}

int Settings::getSeriesDatabase()
{
    return seriesDatabase;
}

int Settings::getNameScheme()
{
    return nameScheme;
}
