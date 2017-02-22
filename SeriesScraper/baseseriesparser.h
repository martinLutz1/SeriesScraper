#ifndef BASESERIESPARSER_H
#define BASESERIESPARSER_H

#include "jsonscraper.h"

class BaseSeriesParser : public JsonScraper
{
public:
    BaseSeriesParser();
    virtual bool scrapeSeries(QString series) = 0;
    virtual QStringList getSeason(int season, QString language) = 0;
    int getAmountSeasons();
    QString getYear();
    QString getSeriesName();
    QString getPosterUrl();
    QString getPlot();

protected:
    QString seriesFullName;
    QString year;
    QString posterUrl;
    QString plot;
    int amountSeasons;

    QString lastScrapedSeries;
};

#endif // BASESERIESPARSER_H
