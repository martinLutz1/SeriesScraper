#include "seriesdata.h"

#include <QDebug>

SeriesData::SeriesData() :
    amountEpisodes(0),
    amountSeasons(0),
    selectedSeason(1)
{
    workingDirectory = QDir("");
}

//----------------------- Setter -----------------------//

void SeriesData::setSeries(QString newSeries)
{
    series = newSeries;
}

void SeriesData::setSuffix(int index, QString newSuffix)
{
    if (suffixesList.length() <= index) { // Prepare space if not enough available
        for (int i = suffixesList.length(); i <= index; i++)
            suffixesList << "";
    }
    suffixesList[index] = newSuffix;
}

void SeriesData::setSuffixes(QStringList newSuffixList)
{
    suffixesList = newSuffixList;
}

void SeriesData::setEpisode(int index, QString newEpisode)
{
    if (episodesList.length() > index)
        episodesList[index] = newEpisode;
}

void SeriesData::setEpisodes(QStringList newEpisodeList)
{
    episodesList = newEpisodeList;
    amountEpisodes = episodesList.length();
}

void SeriesData::setLanguage(QString languageShortName)
{
    language = languageShortName;
}

void SeriesData::setAmountSeasons(int newAmount)
{
    amountSeasons = newAmount;
}

void SeriesData::setSelectedSeason(int newSelectedSeason)
{
    if (newSelectedSeason < amountSeasons)
        selectedSeason = newSelectedSeason;
}

void SeriesData::setOldFileNames(QStringList oldFileNamesSortedWithSpaces)
{
    this->oldFileNamesSortedWithSpaces = oldFileNamesSortedWithSpaces;
}

void SeriesData::setWorkingDirectory(QDir directory)
{
    if (directory.exists())
        workingDirectory = directory;
}

void SeriesData::setNewFileNames(QStringList newFileNames)
{
    this->newFileNames = newFileNames;
}

//----------------------- Getter -----------------------//

QString SeriesData::getSeries()
{
    return series;
}

QString SeriesData::getSuffix(int index)
{
    if (suffixesList.length() > index)
        return suffixesList.at(index);
    else
        return QString("No suffix available at index " + QString::number(index));
}

QStringList SeriesData::getSuffixes()
{
    return suffixesList;
}

QString SeriesData::getEpisode(int index)
{
    if (episodesList.length() > index)
        return episodesList.at(index);
    else
        return QString("No episode available at index " + QString::number(index));
}

QStringList SeriesData::getEpisodes()
{
    return episodesList;
}

QString SeriesData::getLanguage()
{
    return language;
}

int SeriesData::getAmountEpisodes()
{
    return amountEpisodes;
}

int SeriesData::getAmountSeasons()
{
    return amountSeasons;
}

int SeriesData::getSelectedSeason()
{
    return selectedSeason;
}

QStringList SeriesData::getNewFileNames()
{
    return newFileNames;
}

QStringList SeriesData::getOldFileNamesForView()
{
    QStringList oldFileNamesCropped;
    for (int i = 0; i < amountEpisodes; i++) {
        if (i < oldFileNamesSortedWithSpaces.length())
            oldFileNamesCropped << oldFileNamesSortedWithSpaces.at(i);
        else
            oldFileNamesCropped << "";
    }
    return oldFileNamesCropped;
}

QStringList SeriesData::getOldFileNames()
{
    return oldFileNamesSortedWithSpaces;
}

QDir SeriesData::getWorkingDirectory()
{
    return workingDirectory;
}
