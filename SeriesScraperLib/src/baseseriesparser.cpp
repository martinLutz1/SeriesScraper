#include "baseseriesparser.h"

BaseSeriesParser::BaseSeriesParser()
{
}

BaseSeriesParser::~BaseSeriesParser()
{
}

int BaseSeriesParser::getAmountSeasons()
{
    return amountSeasons;
}

QString BaseSeriesParser::getPosterUrl()
{
    return posterUrl;
}

QString BaseSeriesParser::getYear()
{
    return year;
}

QString BaseSeriesParser::getSeriesName()
{
    return seriesFullName;
}

QString BaseSeriesParser::getPlot()
{
    return plot;
}
