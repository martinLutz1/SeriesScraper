#ifndef OMDBSERIESPARSER_H
#define OMDBSERIESPARSER_H

#include <QStringList>
#include "baseseriesparser.h"

class OMDbSeriesParser : public BaseSeriesParser
{
public:
    OMDbSeriesParser();
    bool scrapeSeries(QString series) override;
    QStringList getSeason(int season, QString language="en-EN") override;
};

#endif // OMDBSERIESPARSER_H
