#include "settings.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

Settings::Settings() :
    savePath(1),
    saveSeries(1),
    path(""),
    series(""),
    season(1),
    seriesDatabase(0),
    guiLanguage("English"),
    seriesLanguage("English")
{
    settingsFile.setFileName(QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("settings.json"));
}

Settings::~Settings()
{
    saveSettingsFile();
}

bool Settings::loadSettingsFile()
{
    if (loadJsonObject(settingsFile.fileName()))
    {
        setSavePath(loadedObject.find(jsonKeySavePath).value().toBool());
        setSaveSeries(loadedObject.find(jsonKeySaveSeries).value().toBool());
        setPath(loadedObject.find(jsonKeyPath).value().toString());
        setSeries(loadedObject.find(jsonKeySeries).value().toString());
        setSeason(loadedObject.find(jsonKeySeason).value().toInt());
        setSeriesDatabase(loadedObject.find(jsonKeySeriesDatabase).value().toInt());
        setGuiLanguage(loadedObject.find(jsonKeyGUILanguage).value().toString());
        setSeriesLanguage(loadedObject.find(jsonKeySeriesLanguage).value().toString());
        return true;
    } else
    {
        saveSettingsFile(); // Creates settings file with default values defined in constructor
        return false;
    }
}

void Settings::setSavePath(bool savePathOnExit)
{
    if (savePath != savePathOnExit)
    {
        savePath = savePathOnExit;
        saveSettingsFile();
    }
}

void Settings::setSaveSeries(bool saveSeriesOnExit)
{
    if (saveSeries != saveSeriesOnExit)
    {
        saveSeries = saveSeriesOnExit;
        saveSettingsFile();
    }
}

void Settings::setPath(QString path)
{
    if (this->path != path)
    {
        this->path = path;
        saveSettingsFile();
    }
}

void Settings::setSeries(QString series)
{
    if (this->series != series)
    {
        this->series = series;
        saveSettingsFile();
    }
}

void Settings::setSeason(int season)
{
    if (this->season != season)
    {
        this->season = season;
        saveSettingsFile();
    }
}

void Settings::setSeriesDatabase(int seriesDatabase)
{
    if (this->seriesDatabase != seriesDatabase)
    {
        if (seriesDatabase >= 0 && seriesDatabase <= 1)
            this->seriesDatabase = seriesDatabase;
        else // Set to default if seriesDatabase is not valid
            this->seriesDatabase = 0;
        saveSettingsFile();
    }
}

void Settings::setGuiLanguage(QString guiLanguage)
{
    if (this->guiLanguage != guiLanguage)
    {
        this->guiLanguage = guiLanguage;
        saveSettingsFile();
    }
}

void Settings::setSeriesLanguage(QString seriesLanguage)
{
    if (this->seriesLanguage != seriesLanguage)
    {
        this->seriesLanguage = seriesLanguage;
        saveSettingsFile();
    }
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

    bool successReading = settingsFile.open(QIODevice::ReadWrite | QIODevice::Text);
    if (successReading)
    {
        settingsFile.write(QJsonDocument(jsonSettings).toJson());
        settingsFile.close();
        return true;
    } else
        return false;
}
