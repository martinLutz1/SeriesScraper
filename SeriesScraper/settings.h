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
    void setSeriesDatabase(int seriesDatabase);
    void setGuiLanguage(QString guiLanguage);
    bool getSavePath();
    bool getSaveSeries();
    QString getSeries();
    QString getPath();
    QString getGuiLanguage();
    int getSeriesDatabase();

private:
    QFile settingsFile;
    bool savePath;
    bool saveSeries;
    QString path;
    QString series;
    int seriesDatabase; // 0 = TMDb, 1 = OMDb
    QString guiLanguage;

    const QString jsonKeySavePath = "SavePath";
    const QString jsonKeySaveSeries = "SaveSeries";
    const QString jsonKeyPath= "Path";
    const QString jsonKeySeries = "Series";
    const QString jsonKeySeriesDatabase = "SeriesDatabase";
    const QString jsonKeyGUILanguage = "InterfaceLanguage";

    bool saveSettingsFile();
};

#endif // SETTINGS_H
