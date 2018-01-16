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

private:
    const QString apiKey = "38a6f185";
    const QString baseUrl = "http://www.omdbapi.com/?apikey=" + apiKey + "&t=";
};

#endif // OMDBSERIESPARSER_H
