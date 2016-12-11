#ifndef OMDBSERIESPARSER_H
#define OMDBSERIESPARSER_H

#include <QStringList>
#include "jsonscraper.h"

class OMDbSeriesParser : public JsonScraper
{
public:
    OMDbSeriesParser();
    bool scrapeSeries(QString series);

    QStringList getSeason(int season);
    int getAmountSeasons();
    QString getYear();
    QString getSeriesName();

private:
    QString seriesFullName;
    QString year;
    int amountSeasons;
};

#endif // OMDBSERIESPARSER_H
