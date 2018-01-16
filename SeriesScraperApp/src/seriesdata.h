#ifndef SERIESDATA_H
#define SERIESDATA_H

#include <QString>
#include <QStringList>
#include <QDir>

class SeriesData
{
public:
    SeriesData();
    void setSeries(QString newSeries);
    void setEpisodes(QStringList newEpisodeList);
    void setSelectedLanguage(QString languageShortName);
    void setAmountSeasons(int newAmount);
    void setSelectedSeason(int newSelectedSeason);
    void setWorkingDirectory(QDir directory);
    void setAirDate(QString airDate);
    void setPlot(QString plot);
    void setPosterUrl(QString posterUrl);

    QString getSeries();
    QString getSuffix(int index);
    QStringList getSuffixes();
    QString getEpisode(int index);
    QStringList getEpisodes();
    QString getSelectedLanguage();
    int getAmountEpisodes();
    int getAmountSeasons();
    int getSelectedSeason();
    QStringList getNewFileNames();
    QStringList getNewFileNamesWithoutSuffix();
    QStringList getOldFileNames();
    QStringList getOldFileNamesWithoutSuffix();
    QDir getWorkingDirectory();
    QString getAirDate();
    QString getPlot();
    QString getPosterUrl();

private:
    QString series;
    QStringList suffixesList;
    QStringList episodesList;
    QStringList newFileNamesWithoutSuffix;
    QStringList oldFileNames;
    QStringList oldFileNamesWithoutSuffix;
    QDir workingDirectory;
    int amountSeasons = 0;
    int selectedSeason = 1;
    QString selectedLanguage;
    QString airDate;
    QString plot;
    QString posterUrl;

    QStringList specialCharacterList;
    QString removeSpecialCharacters(QString string);
};

#endif // SERIESDATA_H
