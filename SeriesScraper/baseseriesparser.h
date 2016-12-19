#ifndef BASESERIESPARSER_H
#define BASESERIESPARSER_H

#include "jsonscraper.h"
#include <QTemporaryFile>

class BaseSeriesParser : public JsonScraper
{
public:
    BaseSeriesParser();
    virtual bool scrapeSeries(QString series) = 0;
    virtual QStringList getSeason(int season, QString language) = 0;
    int getAmountSeasons();
    QString getYear();
    QString getSeriesName();

protected:
    QString seriesFullName;
    QString year;
    QString posterUrl;
    int amountSeasons;

};

#endif // BASESERIESPARSER_H
