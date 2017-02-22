#include "seriesparser.h"

SeriesParser::SeriesParser() : selectedSeriesParser(0)
{
    seriesParserVector.push_back(&tmdbSeriesParser);
    seriesParserVector.push_back(&omdbSeriesParser);
    seriesParserVector.push_back(&tvdbSeriesParser);
}

void SeriesParser::setSeriesParser(int seriesParser)
{
    if (seriesParser >= 0 && seriesParser <= 2)
        selectedSeriesParser = seriesParser;
}

int SeriesParser::getSeriesParser()
{
    return selectedSeriesParser;
}

bool SeriesParser::scrapeSeries(QString series)
{
    seriesInput = series;
    return seriesParserVector.at(selectedSeriesParser)->scrapeSeries(series);
}

QString SeriesParser::getSeriesName()
{
    return seriesParserVector.at(selectedSeriesParser)->getSeriesName();
}

QString SeriesParser::getSeriesYear()
{
    return seriesParserVector.at(selectedSeriesParser)->getYear();
}

QString SeriesParser::getPosterUrl()
{
    return seriesParserVector.at(selectedSeriesParser)->getPosterUrl();
}

QString SeriesParser::getPlot()
{
    return seriesParserVector.at(selectedSeriesParser)->getPlot();
}

int SeriesParser::getAmountSeasons()
{
    return seriesParserVector.at(selectedSeriesParser)->getAmountSeasons();
}

QStringList SeriesParser::getEpisodeList(int season, QString language)
{
    int seasonToLoad = season;
    if (season > getAmountSeasons()) // Dont load not existing seasons
        seasonToLoad = 1;

    return seriesParserVector.at(selectedSeriesParser)->getSeason(seasonToLoad, language);
}

QString SeriesParser::getSeriesInput()
{
    return seriesInput;
}
