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
    void setNewFileName(int index, QString newFileName);
    void setEpisodes(QStringList newEpisodeList);
    void setSelectedLanguage(QString languageShortName);
    void setAmountSeasons(int newAmount);
    void setSelectedSeason(int newSelectedSeason);
    void setNewFileNamesWithoutSuffix(QStringList newFileNamesWithoutSuffix);
    void setOldFileNames(QStringList oldFileNames);
    void setOldFileNamesWithoutSuffix(QStringList oldFileNamesWithoutSuffix);
    void setWorkingDirectory(QDir directory);
    void setAirDate(QString airDate);
    void setPosterUrl(QString posterUrl);
    void setPlot(QString plot);

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
    QString getPlot();

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
    QString posterUrl;
    QString plot;

    QStringList specialCharacterList;
    QString removeSpecialCharacters(QString string);
};

#endif // SERIESDATA_H
