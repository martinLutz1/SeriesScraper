#ifndef OMDBSERIESPARSER_H
#define OMDBSERIESPARSER_H

#include <QStringList>
#include "baseseriesparser.h"

class OMDbSeriesParser : public BaseSeriesParser
{
public:
    OMDbSeriesParser();
    bool scrapeSeries(QString series);
    QStringList getSeason(int season, QString language="en-EN");

private:
    QString lastScrapedSeries;
};

#endif // OMDBSERIESPARSER_H
