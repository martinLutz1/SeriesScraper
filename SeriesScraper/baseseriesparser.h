#ifndef BASESERIESPARSER_H
#define BASESERIESPARSER_H

#include "jsonscraper.h"

#include <QByteArray>

class BaseSeriesParser : public JsonScraper
{
public:
    BaseSeriesParser();
    virtual ~BaseSeriesParser();
    virtual bool scrapeSeries(QString series) = 0;
    virtual QStringList getSeason(int season, QString language) = 0;
    int getAmountSeasons();
    QString getPosterUrl();
    QString getYear();
    QString getSeriesName();
    QString getPlot();

protected:
    QString seriesFullName;
    QString posterUrl;
    QString year;
    QString plot;
    int amountSeasons;
    QString lastScrapedSeries;
};

#endif // BASESERIESPARSER_H
