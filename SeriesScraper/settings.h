#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QFile>
#include "jsonloader.h"


class Settings : public JsonLoader
{
public:
    Settings();
    bool loadSettingsFile();
    bool saveSettingsFile();
    bool resetSettingsFile();

    void setSavePath(bool savePathOnExit);
    void setSaveSeries(bool saveSeriesOnExit);
    void setSavePosterInDirectory(bool savePosterInDirectory);
    void setAutoSetDetectedSeason(bool autoSetDetectedSeason);
    void setDarkTheme(bool useDarkTheme);
    void setShowSeriesInfo(bool showSeriesInfo);
    void setPath(QString path);
    void setSeries(QString series);
    void setSeason(int season);
    void setSeriesDatabase(int seriesDatabase);
    void setNameScheme(int nameScheme);
    void setGuiLanguage(QString guiLanguage);
    void setSeriesLanguage(QString seriesLanguage);

    bool getSavePath();
    bool getSaveSeries();
    bool getSavePosterInDirectory();
    bool getAutoSetDetectedSeason();
    bool getDarkTheme();
    bool getShowSeriesInfo();
    QString getPath();
    QString getSeries();
    QString getGuiLanguage();
    QString getSeriesLanguage();
    int getSeason();
    int getSeriesDatabase();
    int getNameScheme();

private:
    void setDefaultValues();
    QFile settingsFile;
    bool savePath;
    bool saveSeries;
    bool savePosterInDirectory;
    bool autoSetDetectedSeason;
    bool useDarkTheme;
    bool showSeriesInfo;
    QString path;
    QString series;
    int season;
    int seriesDatabase; // 0 = TMDb, 1 = OMDb
    int nameScheme;
    QString guiLanguage;
    QString seriesLanguage;

    const QString jsonKeySavePath = "SavePath";
    const QString jsonKeySaveSeries = "SaveSeries";
    const QString jsonKeySavePosterInDirectory = "SavePosterInDirectory";
    const QString jsonKeyAutoSetDetectedSeason = "AutoSetDetectedSeason";
    const QString jsonKeyDarkTheme = "DarkTheme";
    const QString jsonKeyShowSeriesInfo = "ShowSeriesInfo";
    const QString jsonKeyPath = "Path";
    const QString jsonKeySeries = "Series";
    const QString jsonKeySeason = "Season";
    const QString jsonKeySeriesDatabase = "SeriesDatabase";
    const QString jsonKeyNameScheme = "NameScheme";
    const QString jsonKeyGUILanguage = "InterfaceLanguage";
    const QString jsonKeySeriesLanguage = "SeriesLanguage";

    const bool defaultSavePath = false;
    const bool defaultSaveSeries = false;
    const bool defaultSavePosterInDirectory = false;
    const bool defaultAutoSetDetectedSeason = false;
    const bool defaultUseDarkTheme = false;
    const bool defaultShowSeriesInfo = true;
    const QString defaultPath = "";
    const QString defaultSeries = "";
    const int defaultSeason = 1;
    const int defaultSeriesDatabase = 0;
    const int defaultNameScheme = 0;
    const QString defaultGuiLanguage = "English";
    const QString defaultSeriesLanguage = "English";
};

#endif // SETTINGS_H
