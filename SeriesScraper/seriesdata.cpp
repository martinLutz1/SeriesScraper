#include "seriesdata.h"

#include <QDebug>

SeriesData::SeriesData() :
    amountEpisodes(0),
    amountSeasons(0),
    selectedSeason(1)
{
    workingDirectory = QDir("");
    specialCharacterList << "<" << ">" << ":" << "\"" << "/" << "|" << "?" << "*";
}

//----------------------- Setter -----------------------//

void SeriesData::setSeries(QString newSeries)
{
    series = removeSpecialCharacters(newSeries);
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
    if (index == episodesList.size() - 1 && newEpisode == "") // Last item
        episodesList.removeLast();
    else
    {
       while (index >= episodesList.size())
            episodesList.push_back(" ");

        QString newEpisodeWithoutSpecialCharacters = removeSpecialCharacters(newEpisode);
        episodesList[index] = newEpisodeWithoutSpecialCharacters;
    }
    amountEpisodes = episodesList.size();
}

void SeriesData::setEpisodes(QStringList newEpisodeList)
{
    int numberEpisodes = newEpisodeList.size();
    QStringList epiosodeListWithoutSpecialCharacters;
    for (int i = 0; i < numberEpisodes; i++)
        epiosodeListWithoutSpecialCharacters << removeSpecialCharacters(newEpisodeList.at(i));

    episodesList = epiosodeListWithoutSpecialCharacters;
    amountEpisodes = episodesList.size();
}

void SeriesData::setSelectedLanguage(QString languageShortName)
{
    selectedLanguage = languageShortName;
}

void SeriesData::setAmountSeasons(int newAmount)
{
    amountSeasons = newAmount;
}

void SeriesData::setSelectedSeason(int newSelectedSeason)
{
    if (newSelectedSeason <= amountSeasons)
        selectedSeason = newSelectedSeason;
}

void SeriesData::setNewFileNames(QStringList newFileNames)
{
    this->newFileNames = newFileNames;
}

void SeriesData::setNewFileNamesWithoutSuffix(QStringList newFileNamesWithoutSuffix)
{
    this->newFileNamesWithoutSuffix = newFileNamesWithoutSuffix;
}

void SeriesData::setOldFileNames(QStringList oldFileNames)
{
    this->oldFileNames = oldFileNames;
}

void SeriesData::setOldFileNamesWithoutSuffix(QStringList oldFileNamesWithoutSuffix)
{
    this->oldFileNamesWithoutSuffix = oldFileNamesWithoutSuffix;
}

void SeriesData::setWorkingDirectory(QDir directory)
{
    if (directory.exists())
        workingDirectory = directory;
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
        return QString("");
}

QStringList SeriesData::getEpisodes()
{
    return episodesList;
}

QString SeriesData::getSelectedLanguage()
{
    return selectedLanguage;
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

QStringList SeriesData::getNewFileNamesWithoutSuffix()
{
    return newFileNamesWithoutSuffix;
}

QStringList SeriesData::getOldFileNames()
{
    return oldFileNames;
}

QStringList SeriesData::getOldFileNamesWithoutSuffix()
{
    return oldFileNamesWithoutSuffix;
}

QDir SeriesData::getWorkingDirectory()
{
    return workingDirectory;
}

QString SeriesData::removeSpecialCharacters(QString string)
{
    QString stringWithoutSpecialCharacters = string;
    for (int i = 0; i < specialCharacterList.size(); i++)
        stringWithoutSpecialCharacters.replace(specialCharacterList.at(i), "");
    return stringWithoutSpecialCharacters;
}
