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
    void setSelectedLanguage(QString languageShortName);
    void setAmountSeasons(int newAmount);
    void setSelectedSeason(int newSelectedSeason);
    void setNewFileNames(QStringList newFileNames);
    void setNewFileNamesWithoutSuffix(QStringList newFileNamesWithoutSuffix);
    void setOldFileNames(QStringList oldFileNames);
    void setOldFileNamesWithoutSuffix(QStringList oldFileNamesWithoutSuffix);
    void setWorkingDirectory(QDir directory);
    void setAirDate(QString airDate);
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
    QString getPosterUrl();

private:
    QString series;
    QStringList suffixesList;
    QStringList episodesList;
    QStringList newFileNames;
    QStringList newFileNamesWithoutSuffix;
    QStringList oldFileNames;
    QStringList oldFileNamesWithoutSuffix;
    QDir workingDirectory;
    int amountEpisodes;
    int amountSeasons;
    int selectedSeason;
    QString selectedLanguage;
    QString airDate;
    QString posterUrl;

    QStringList specialCharacterList;
    QString removeSpecialCharacters(QString string);
};

#endif // SERIESDATA_H
