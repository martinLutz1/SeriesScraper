#include "settings.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

Settings::Settings()
{
    settingsFile.setFileName(QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("settings.json"));
    savePath = defaultSavePath;
    saveSeries = defaultSaveSeries;
    path = defaultPath;
    series = defaultSeries;
    season = defaultSeason;
    seriesDatabase = defaultSeriesDatabase;
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
        setPath(loadedObject.find(jsonKeyPath).value().toString());
        setSeries(loadedObject.find(jsonKeySeries).value().toString());
        setSeason(loadedObject.find(jsonKeySeason).value().toInt());
        setSeriesDatabase(loadedObject.find(jsonKeySeriesDatabase).value().toInt());
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
    jsonSettings.insert(jsonKeySaveSeries, saveSeries);
    jsonSettings.insert(jsonKeySeries, series);
    jsonSettings.insert(jsonKeySeriesDatabase, seriesDatabase);
    jsonSettings.insert(jsonKeyGUILanguage, guiLanguage);
    jsonSettings.insert(jsonKeySeriesLanguage, seriesLanguage);
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
    path = defaultPath;
    series = defaultSeries;
    season = defaultSeason;
    seriesDatabase = defaultSeriesDatabase;
    guiLanguage = defaultGuiLanguage;
    seriesLanguage = defaultSeriesLanguage;
    return saveSettingsFile();
}

void Settings::setSavePath(bool savePathOnExit)
{
    if (savePath != savePathOnExit)
        savePath = savePathOnExit;
}

void Settings::setSaveSeries(bool saveSeriesOnExit)
{
    if (saveSeries != saveSeriesOnExit)
        saveSeries = saveSeriesOnExit;
}

void Settings::setPath(QString path)
{
    if (this->path != path)
        this->path = path;
}

void Settings::setSeries(QString series)
{
    if (series.isEmpty())
        this->series.clear();
    else if (this->series != series)
        this->series = series;
}

void Settings::setSeason(int season)
{
    if (this->season != season)
        this->season = season;
}

void Settings::setSeriesDatabase(int seriesDatabase)
{
    if (this->seriesDatabase != seriesDatabase)
    {
        if (seriesDatabase >= 0 && seriesDatabase <= 1)
            this->seriesDatabase = seriesDatabase;
        else // Set to default if seriesDatabase is not valid
            this->seriesDatabase = 0;
    }
}

void Settings::setGuiLanguage(QString guiLanguage)
{
    if (this->guiLanguage != guiLanguage)
        this->guiLanguage = guiLanguage;
}

void Settings::setSeriesLanguage(QString seriesLanguage)
{
    if (this->seriesLanguage != seriesLanguage)
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
