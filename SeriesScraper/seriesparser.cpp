#include "seriesparser.h"

SeriesParser::SeriesParser() : selectedSeriesParser(0)
{

}

void SeriesParser::setSeriesParser(int seriesParser)
{
    if (seriesParser >= 0 && seriesParser <= 1)
        selectedSeriesParser = seriesParser;
}

int SeriesParser::getSeriesParser()
{
    return selectedSeriesParser;
}

bool SeriesParser::scrapeSeries(QString series)
{
    seriesInput = series;
    switch(selectedSeriesParser)
    {
    default:
    case tmdb:
    {
        return tmdbSeriesParser.scrapeSeries(series);
        break;
    }
    case omdb:
    {
        return omdbSeriesParser.scrapeSeries(series);
        break;
    }
    }
}

QString SeriesParser::getSeriesName()
{
    switch(selectedSeriesParser)
    {
    default:
    case tmdb:
    {
        return tmdbSeriesParser.getSeriesName();
        break;
    }
    case omdb:
    {
        return omdbSeriesParser.getSeriesName();
        break;
    }
    }
}

QString SeriesParser::getSeriesYear()
{
    switch(selectedSeriesParser)
    {
    default:
    case tmdb:
    {
        return tmdbSeriesParser.getYear();
        break;
    }
    case omdb:
    {
        return omdbSeriesParser.getYear();
        break;
    }
    }
}

int SeriesParser::getAmountSeasons()
{
    switch(selectedSeriesParser)
    {
    default:
    case tmdb:
    {
        return tmdbSeriesParser.getAmountSeasons();
        break;
    }
    case omdb:
    {
        return omdbSeriesParser.getAmountSeasons();
        break;
    }
    }
}

QStringList SeriesParser::getEpisodeList(int season, QString language)
{
    switch(selectedSeriesParser)
    {
    default:
    case tmdb:
    {
        return tmdbSeriesParser.getSeason(season, language);
        break;
    }
    case omdb:
    {
        return omdbSeriesParser.getSeason(season);
        break;
    }
    }
}

QString SeriesParser::getSeriesInput()
{
    return seriesInput;
}
