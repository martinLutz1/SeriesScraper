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
    void setLanguage(QString languageShortName);
    void setAmountSeasons(int newAmount);
    void setSelectedSeason(int newSelectedSeason);
    void setOldFileNames(QStringList oldFileNamesSortedWithSpaces);
    void setOldFileNamesWithoutExtionsions(QStringList oldFileNameListWithoutExtensions);
    void setWorkingDirectory(QDir directory);
    void setNewFileNames(QStringList newFileNames);

    QString getSeries();
    QString getSuffix(int index);
    QStringList getSuffixes();
    QString getEpisode(int index);
    QStringList getEpisodes();
    QString getLanguage();
    int getAmountEpisodes();
    int getAmountSeasons();
    int getSelectedSeason();
    QStringList getNewFileNames();
    QStringList getOldFileNames();
    QStringList getOldFileNamesWithoutExtensions();
    QDir getWorkingDirectory();

private:
    QString series;
    QStringList suffixesList;
    QStringList episodesList;
    QStringList oldFileNamesSortedWithSpaces;
    QStringList oldFileNamesWithoutExtensions;
    QStringList newFileNames;
    QDir workingDirectory;
    int amountEpisodes;
    int amountSeasons;
    int selectedSeason;
    QString language;
};

#endif // SERIESDATA_H
