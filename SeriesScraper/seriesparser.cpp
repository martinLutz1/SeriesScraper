#include "seriesparser.h"

SeriesParser::SeriesParser()
{
    setSeriesParser(selectedSeriesParser);
}

SeriesParser::~SeriesParser()
{
    parser = nullptr;
}

void SeriesParser::setSeriesParser(Parser selectedSeriesParser)
{
    switch (selectedSeriesParser)
    {
    case Parser::tmdb:
        this->selectedSeriesParser = selectedSeriesParser;
        parser = &tmdbSeriesParser;
        break;

    case Parser::omdb:
        this->selectedSeriesParser = selectedSeriesParser;
        parser = &omdbSeriesParser;
        break;

    case Parser::tvdb:
        this->selectedSeriesParser = selectedSeriesParser;
        parser = &tvdbSeriesParser;
        break;

    default:
        qDebug() << "Selected not available series parser with index " + QString::number((int)selectedSeriesParser);
        break;
    }
}

SeriesParser::Parser SeriesParser::getSeriesParserIndex()
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
