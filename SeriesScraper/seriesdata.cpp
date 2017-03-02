#include "seriesdata.h"

#include <QDebug>

SeriesData::SeriesData()
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

void SeriesData::setNewFileName(int index, QString newFileName)
{
    while (index >= newFileNamesWithoutSuffix.size())
        newFileNamesWithoutSuffix.push_back("");

    newFileNamesWithoutSuffix[index] = removeSpecialCharacters(newFileName);
}

void SeriesData::setEpisodes(QStringList newEpisodeList)
{
    int numberEpisodes = newEpisodeList.size();
    QStringList epiosodeListWithoutSpecialCharacters;
    for (int i = 0; i < numberEpisodes; i++)
        epiosodeListWithoutSpecialCharacters << removeSpecialCharacters(newEpisodeList.at(i));

    episodesList = epiosodeListWithoutSpecialCharacters;
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

void SeriesData::setAirDate(QString airDate)
{
    this->airDate = airDate;
}

void SeriesData::setPosterUrl(QString posterUrl)
{
    this->posterUrl = posterUrl;
}

void SeriesData::setPlot(QString plot)
{
    this->plot = plot;
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
    return episodesList.size();;
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
    QStringList newFileNames;
    int minimumSize = std::min(newFileNamesWithoutSuffix.size(), suffixesList.size());
    for (int i = 0; i < minimumSize; i++)
    {
        if (newFileNamesWithoutSuffix.at(i).isEmpty() || suffixesList.at(i).isEmpty())
            newFileNames << "";
        else
            newFileNames << (newFileNamesWithoutSuffix.at(i) + "." + suffixesList.at(i));
    }
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

QString SeriesData::getAirDate()
{
    return airDate;
}

QString SeriesData::getPosterUrl()
{
    return posterUrl;
}

QString SeriesData::getPlot()
{
    return plot;
}

QString SeriesData::removeSpecialCharacters(QString string)
{
    QString stringWithoutSpecialCharacters = string;
    for (int i = 0; i < specialCharacterList.size(); i++)
        stringWithoutSpecialCharacters.replace(specialCharacterList.at(i), "");
    return stringWithoutSpecialCharacters;
}
