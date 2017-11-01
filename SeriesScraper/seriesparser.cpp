#include "seriesparser.h"

SeriesParser::SeriesParser()
{
    setSeriesParser(selectedSeriesParser);
}

SeriesParser::~SeriesParser()
{
    parser = nullptr;
}

void SeriesParser::setSeriesParser(int selectedSeriesParser)
{
    switch (selectedSeriesParser)
    {
    case seriesParser::tmdb:
        this->selectedSeriesParser = selectedSeriesParser;
        parser = &tmdbSeriesParser;
        break;

    case seriesParser::omdb:
        this->selectedSeriesParser = selectedSeriesParser;
        parser = &omdbSeriesParser;
        break;

    case seriesParser::tvdb:
        this->selectedSeriesParser = selectedSeriesParser;
        parser = &tvdbSeriesParser;
        break;
    default:
        qDebug() << "Selected not available series parser with index " + QString::number(selectedSeriesParser);
        break;
    }
}

int SeriesParser::getSeriesParserIndex()
{
    return selectedSeriesParser;
}

void SeriesParser::setSeriesInput(QString series)
{
    seriesInput = series;
}

BaseSeriesParser *SeriesParser::getSeriesParser()
{
    return parser;
}

QString SeriesParser::getSeriesInput()
{
    return seriesInput;
}
