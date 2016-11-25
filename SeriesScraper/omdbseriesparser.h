#ifndef OMDBSERIESPARSER_H
#define OMDBSERIESPARSER_H

#include <QStringList>
#include "jsonscraper.h"

class OMDbSeriesParser : public JsonScraper
{
private:
    QStringList episodeList;
    int amountSeasons;

public:
    OMDbSeriesParser();
    bool scrapeSeries(QString series, int season);

    QStringList getEpisodeList();
    int getAmountSeasons();
};

#endif // OMDBSERIESPARSER_H
