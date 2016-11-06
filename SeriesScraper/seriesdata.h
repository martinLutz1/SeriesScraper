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
    void setSuffix(int index, QString newSuffix);
    void setSuffixes(QStringList newSuffixList);
    void setEpisode(int index, QString newEpisode);
    void setEpisodes(QStringList newEpisodeList);
    void setAmountSeasons(int newAmount);
    void setSelectedSeason(int newSelectedSeason);
    void setOldFileNames(QStringList oldFileNamesSortedWithSpaces);
    void setWorkingDirectory(QDir directory);
    void setNewFileNames(QStringList newFileNames);

    QString getSeries();
    QString getSuffix(int index);
    QStringList getSuffixes();
    QString getEpisode(int index);
    QStringList getEpisodes();
    int getAmountEpisodes();
    int getAmountSeasons();
    int getSelectedSeason();
    QStringList getNewFileNames();
    QStringList getOldFileNamesForView();
    QStringList getOldFileNames();
    QDir getWorkingDirectory();

private:
    QString series;
    QStringList suffixesList;
    QStringList episodesList;
    QStringList oldFileNamesSortedWithSpaces;
    QStringList newFileNames;
    QDir workingDirectory;
    int amountEpisodes;
    int amountSeasons;
    int selectedSeason;
};

#endif // SERIESDATA_H
