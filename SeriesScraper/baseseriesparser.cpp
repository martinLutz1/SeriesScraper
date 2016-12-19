#include "baseseriesparser.h"

BaseSeriesParser::BaseSeriesParser()
{
}

int BaseSeriesParser::getAmountSeasons()
{
    return amountSeasons;
}

QString BaseSeriesParser::getYear()
{
    return year;
}

QString BaseSeriesParser::getSeriesName()
{
    return seriesFullName;
}

QString BaseSeriesParser::getPosterUrl()
{
    return posterUrl;
}
