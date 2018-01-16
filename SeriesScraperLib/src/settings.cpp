#include "settings.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

Settings::Settings()
{
    setDefaultValues();
}

bool Settings::loadSettingsFile()
{
    bool loadingSuccessful = loadJsonObject(settingsFile.fileName());
    if (loadingSuccessful)
    {
        setSavePath(loadedObject.find(jsonKeySavePath).value().toBool());
        setSaveSeries(loadedObject.find(jsonKeySaveSeries).value().toBool());
        setSavePosterInDirectory(loadedObject.find(jsonKeySavePosterInDirectory).value().toBool());
        setAutoSetDetectedSeason(loadedObject.find(jsonKeyAutoSetDetectedSeason).value().toBool());
        setDarkTheme(loadedObject.find(jsonKeyDarkTheme).value().toBool());
        setShowSeriesInfo(loadedObject.find(jsonKeyShowSeriesInfo).value().toBool());
        setDirectoryView(loadedObject.find(jsonKeyDirectoryView).value().toString());
        setPath(loadedObject.find(jsonKeyPath).value().toString());
        setSeries(loadedObject.find(jsonKeySeries).value().toString());
        setSeason(loadedObject.find(jsonKeySeason).value().toInt());
        setSeriesDatabase((SeriesParser::Parser)loadedObject.find(jsonKeySeriesDatabase).value().toInt());
        setNameScheme(loadedObject.find(jsonKeyNameScheme).value().toInt());
        setGuiLanguage(loadedObject.find(jsonKeyGUILanguage).value().toString());
        setSeriesLanguage(loadedObject.find(jsonKeySeriesLanguage).value().toString());

        // Window position and size.
        int x = loadedObject.find(jsonKeyWindowPosX).value().toInt();
        int y = loadedObject.find(jsonKeyWindowPosY).value().toInt();
        int width = loadedObject.find(jsonKeyWindowWidth).value().toInt();
        int height = loadedObject.find(jsonKeyWindowHeight).value().toInt();
        setWindowRect(QRect(x, y, width, height));
    }
    else
    {
        // Creates settings file with default values defined in constructor.
        saveSettingsFile();
    }

    return loadingSuccessful;
}

bool Settings::saveSettingsFile()
{
    QJsonObject jsonSettings;
    jsonSettings.insert(jsonKeySavePath, savePath);
    jsonSettings.insert(jsonKeyPath, path);
    jsonSettings.insert(jsonKeyDirectoryView, directoryView);
    jsonSettings.insert(jsonKeyDarkTheme, useDarkTheme);
    jsonSettings.insert(jsonKeyShowSeriesInfo, showSeriesInfo);
    jsonSettings.insert(jsonKeySaveSeries, saveSeries);
    jsonSettings.insert(jsonKeySeries, series);
    jsonSettings.insert(jsonKeySavePosterInDirectory, savePosterInDirectory);
    jsonSettings.insert(jsonKeyAutoSetDetectedSeason, autoSetDetectedSeason);
    jsonSettings.insert(jsonKeySeriesDatabase, (int)seriesDatabase);
    jsonSettings.insert(jsonKeyGUILanguage, guiLanguage);
    jsonSettings.insert(jsonKeySeriesLanguage, seriesLanguage);
    jsonSettings.insert(jsonKeyNameScheme, nameScheme);
    jsonSettings.insert(jsonKeySeason, season);
    jsonSettings.insert(jsonKeyWindowPosX, windowPosX);
    jsonSettings.insert(jsonKeyWindowPosY, windowPosY);
    jsonSettings.insert(jsonKeyWindowWidth, windowWidth);
    jsonSettings.insert(jsonKeyWindowHeight, windowHeight);

    bool successReading = settingsFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    if (successReading)
    {
        settingsFile.write(QJsonDocument(jsonSettings).toJson());
    }
    settingsFile.close();

    return successReading;
}

bool Settings::resetSettingsFile()
{
    setDefaultValues();
    return saveSettingsFile();
}

void Settings::setSavePath(bool savePathOnExit)
{
    this->savePath = savePathOnExit;
}

void Settings::setSaveSeries(bool saveSeriesOnExit)
{
    this->saveSeries = saveSeriesOnExit;
}

void Settings::setSavePosterInDirectory(bool savePosterInDirectory)
{
    this->savePosterInDirectory = savePosterInDirectory;
}

void Settings::setAutoSetDetectedSeason(bool autoSetDetectedSeason)
{
    this->autoSetDetectedSeason = autoSetDetectedSeason;
}

void Settings::setDarkTheme(bool useDarkTheme)
{
    this->useDarkTheme = useDarkTheme;
}

void Settings::setShowSeriesInfo(bool showSeriesInfo)
{
    this->showSeriesInfo = showSeriesInfo;
}

void Settings::setDirectoryView(DirectorySelector directoryView)
{
    if (DirectorySelector::widget == directoryView)
    {
        this->directoryView = "Widget";
    }
    else if (DirectorySelector::text == directoryView)
    {
        this->directoryView = "Text";
    }
}

void Settings::setDirectoryView(QString directoryView)
{
    this->directoryView = directoryView;
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

void Settings::setSeriesDatabase(SeriesParser::Parser seriesDatabase)
{
    this->seriesDatabase = seriesDatabase;
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

void Settings::setWindowRect(QRect windowRect)
{
    windowPosX = windowRect.x();
    windowPosY = windowRect.y();
    windowWidth = windowRect.width();
    windowHeight = windowRect.height();
}

bool Settings::getSavePath()
{
    return savePath;
}

bool Settings::getSaveSeries()
{
    return saveSeries;
}

bool Settings::getSavePosterInDirectory()
{
    return savePosterInDirectory;
}

bool Settings::getAutoSetDetectedSeason()
{
    return autoSetDetectedSeason;
}

bool Settings::getDarkTheme()
{
    return useDarkTheme;
}

bool Settings::getShowSeriesInfo()
{
    return showSeriesInfo;
}

Settings::DirectorySelector Settings::getDirectoryView()
{
    if (directoryView.toLower() == "text")
    {
        return DirectorySelector::text;
    }

    return DirectorySelector::widget;
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

SeriesParser::Parser Settings::getSeriesDatabase()
{
    return seriesDatabase;
}

int Settings::getNameScheme()
{
    return nameScheme;
}

QRect Settings::getWindowRect()
{
    return QRect(windowPosX, windowPosY, windowWidth, windowHeight);
}

void Settings::setDefaultValues()
{
    settingsFile.setFileName(QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("settings.json"));
    savePath = defaultSavePath;
    saveSeries = defaultSaveSeries;
    savePosterInDirectory = defaultSavePosterInDirectory;
    autoSetDetectedSeason = defaultAutoSetDetectedSeason;
    useDarkTheme = defaultUseDarkTheme;
    showSeriesInfo = defaultShowSeriesInfo;
    directoryView = defaultDirectoryView;
    path = defaultPath;
    series = defaultSeries;
    season = defaultSeason;
    seriesDatabase = defaultSeriesDatabase;
    nameScheme = defaultNameScheme;
    guiLanguage = defaultGuiLanguage;
    seriesLanguage = defaultSeriesLanguage;
    windowPosX = defaultWindowPosX;
    windowPosY = defaultWindowPosY;
    windowWidth = defaultWindowWidth;
    windowHeight = defaultWindowHeight;
}
