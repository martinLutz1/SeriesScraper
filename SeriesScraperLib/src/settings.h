#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QFile>
#include <QRect>
#include "jsonloader.h"
#include "seriesparser.h" // Parser enum.


class Settings : public JsonLoader
{
public:
    enum class DirectorySelector { widget, text };
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
    void setDirectoryView(DirectorySelector directoryView);
    void setDirectoryView(QString directoryView);
    void setPath(QString path);
    void setSeries(QString series);
    void setSeason(int season);
    void setSeriesDatabase(SeriesParser::Parser seriesDatabase);
    void setNameScheme(int nameScheme);
    void setGuiLanguage(QString guiLanguage);
    void setSeriesLanguage(QString seriesLanguage);
    void setWindowRect(QRect windowRect);

    bool getSavePath();
    bool getSaveSeries();
    bool getSavePosterInDirectory();
    bool getAutoSetDetectedSeason();
    bool getDarkTheme();
    bool getShowSeriesInfo();
    DirectorySelector getDirectoryView();
    QString getPath();
    QString getSeries();
    QString getGuiLanguage();
    QString getSeriesLanguage();
    int getSeason();
    SeriesParser::Parser getSeriesDatabase();
    int getNameScheme();
    QRect getWindowRect();

private:
    void setDefaultValues();
    QFile settingsFile;
    bool savePath;
    bool saveSeries;
    bool savePosterInDirectory;
    bool autoSetDetectedSeason;
    bool useDarkTheme;
    bool showSeriesInfo;
    QString directoryView;
    QString path;
    QString series;
    int season;
    SeriesParser::Parser seriesDatabase;
    int nameScheme;
    QString guiLanguage;
    QString seriesLanguage;
    int windowPosX;
    int windowPosY;
    int windowWidth;
    int windowHeight;

    const QString jsonKeySavePath = "SavePath";
    const QString jsonKeySaveSeries = "SaveSeries";
    const QString jsonKeySavePosterInDirectory = "SavePosterInDirectory";
    const QString jsonKeyAutoSetDetectedSeason = "AutoSetDetectedSeason";
    const QString jsonKeyDirectoryView = "DirectoryView";
    const QString jsonKeyDarkTheme = "DarkTheme";
    const QString jsonKeyShowSeriesInfo = "ShowSeriesInfo";
    const QString jsonKeyPath = "Path";
    const QString jsonKeySeries = "Series";
    const QString jsonKeySeason = "Season";
    const QString jsonKeySeriesDatabase = "SeriesDatabase";
    const QString jsonKeyNameScheme = "NameScheme";
    const QString jsonKeyGUILanguage = "InterfaceLanguage";
    const QString jsonKeySeriesLanguage = "SeriesLanguage";
    const QString jsonKeyWindowPosX = "WindowPosX";
    const QString jsonKeyWindowPosY = "WindowPosY";
    const QString jsonKeyWindowWidth = "WindowWidth";
    const QString jsonKeyWindowHeight = "WindowHeight";

    const bool defaultSavePath = false;
    const bool defaultSaveSeries = false;
    const bool defaultSavePosterInDirectory = false;
    const bool defaultAutoSetDetectedSeason = false;
    const bool defaultUseDarkTheme = false;
    const bool defaultShowSeriesInfo = true;
    const QString defaultDirectoryView = "Widget";
    const QString defaultPath = "";
    const QString defaultSeries = "";
    const int defaultSeason = 1;
    const SeriesParser::Parser defaultSeriesDatabase = SeriesParser::Parser::tmdb;
    const int defaultNameScheme = 0;
    const QString defaultGuiLanguage = "English";
    const QString defaultSeriesLanguage = "English";
    const int defaultWindowPosX = -1;
    const int defaultWindowPosY = -1;
    const int defaultWindowWidth = 0;
    const int defaultWindowHeight = 0;
};

#endif // SETTINGS_H
