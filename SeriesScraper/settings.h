#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QFile>
#include "jsonloader.h"


class Settings : public JsonLoader
{
public:
    Settings();
    ~Settings();
    bool loadSettingsFile();

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

    bool saveSettingsFile();
};

#endif // SETTINGS_H
