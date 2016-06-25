#include "languagedata.h"

LanguageData::LanguageData() :
    episodeName("Episode name"),
    fileName("File name"),
    directorySelection("Directory selection"),
    path("Path"),
    selection("Selection"),
    series("Series"),
    seriesSelection("Series selection"),
    season("Season"),
    episode("Episode")
{
}

QString LanguageData::getEpisodeName()
{
    return episodeName;
}

QString LanguageData::getFileName()
{
    return fileName;
}

QString LanguageData::getDirectorySelection()
{
    return directorySelection;
}

QString LanguageData::getPath()
{
    return path;
}

QString LanguageData::getSelection()
{
    return selection;
}

QString LanguageData::getSeries()
{
    return series;
}

QString LanguageData::getSeriesSelection()
{
    return seriesSelection;
}

QString LanguageData::getSeason()
{
    return season;
}

QString LanguageData::getEpisode()
{
    return episode;
}



void LanguageData::setEpisodeName(QString newEpisodeName)
{
    this->episodeName = newEpisodeName;
}

void LanguageData::setFileName(QString newFileName)
{
    this->fileName = newFileName;
}

void LanguageData::setDirectorySelection(QString newDirectorySelection)
{
    this->directorySelection = newDirectorySelection;
}

void LanguageData::setPath(QString newPath)
{
    this->path = newPath;
}

void LanguageData::setSelection(QString newSelection)
{
    this->selection = newSelection;
}

void LanguageData::setSeries(QString newSeries)
{
    this->series = newSeries;
}

void LanguageData::setSeriesSelection(QString newSeriesSelection)
{
    this->seriesSelection = newSeriesSelection;
}

void LanguageData::setSeason(QString newSeason)
{
    this->season = newSeason;
}

void LanguageData::setEpisode(QString newEpisode)
{
    this->episode = newEpisode;
}
