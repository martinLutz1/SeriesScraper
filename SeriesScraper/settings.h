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
    void setPath(QString path);
    void setSeries(QString series);
    void setSeason(int season);
    void setSeriesDatabase(int seriesDatabase);
    void setGuiLanguage(QString guiLanguage);
    void setSeriesLanguage(QString seriesLanguage);
    bool getSavePath();
    bool getSaveSeries();
    QString getPath();
    QString getSeries();
    QString getGuiLanguage();
    QString getSeriesLanguage();
    int getSeason();
    int getSeriesDatabase();

private:
    QFile settingsFile;
    bool savePath;
    bool saveSeries;
    QString path;
    QString series;
    int season;
    int seriesDatabase; // 0 = TMDb, 1 = OMDb
    QString guiLanguage;
    QString seriesLanguage;

    const QString jsonKeySavePath = "SavePath";
    const QString jsonKeySaveSeries = "SaveSeries";
    const QString jsonKeyPath= "Path";
    const QString jsonKeySeries = "Series";
    const QString jsonKeySeason = "Season";
    const QString jsonKeySeriesDatabase = "SeriesDatabase";
    const QString jsonKeyGUILanguage = "InterfaceLanguage";
    const QString jsonKeySeriesLanguage = "SeriesLanguage";

    const bool defaultSavePath = false;
    const bool defaultSaveSeries = false;
    const QString defaultPath = "";
    const QString defaultSeries = "";
    const int defaultSeason = 1;
    const int defaultSeriesDatabase = 0;
    const QString defaultGuiLanguage = "English";
    const QString defaultSeriesLanguage = "English";
};

#endif // SETTINGS_H
