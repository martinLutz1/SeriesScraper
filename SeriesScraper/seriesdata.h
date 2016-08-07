#ifndef SERIESDATA_H
#define SERIESDATA_H

#include <QString>
#include <QStringList>
#include <QDir>


class SeriesData
{
public:
    SeriesData();
    void setSeriesFileNameText(QString newSeriesText);
    void setSeasonFileNameText(QString newSeasonText);
    void setEpisodeFileNameText(QString newEpisodeText);
    void setSeries(QString newSeries);
    void setSuffix(int index, QString newSuffix);
    void setSuffixes(QStringList newSuffixList);
    void setEpisode(int index, QString newEpisode);
    void setEpisodes(QStringList newEpisodeList);
    void setAmountSeasons(int newAmount);
    void setSelectedSeason(int newSelectedSeason);
    void setOldFileNames(QStringList oldFileNamesSortedWithSpaces);
    void setWorkingDirectory(QDir directory);

    QString getSeriesFileNameText();
    QString getSeasonFileNameText();
    QString getEpisodeFileNameText();
    QString getSeries();
    QString getSuffix(int index);
    QString getEpisode(int index);
    QStringList getEpisodes();
    int getAmountEpisodes();
    int getAmountSeasons();
    int getSelectedSeason();
    QString getFileNameText(int index);
    QStringList getNewFileNamesForView();
    QStringList getOldFileNamesForView();
    QDir getWorkingDirectory();

private:
    QString seriesFileNameText;
    QString seasonFileNameText;
    QString episodeFileNameText;
    QString series;
    QStringList suffixesList;
    QStringList episodesList;
    QStringList oldFileNamesSortedWithSpaces;
    QDir workingDirectory;
    int amountEpisodes;
    int amountSeasons;
    int selectedSeason;
};

#endif // SERIESDATA_H
