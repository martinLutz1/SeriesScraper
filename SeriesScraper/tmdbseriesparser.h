#ifndef TMDBSERIESPARSER_H
#define TMDBSERIESPARSER_H

#include "jsonscraper.h"
#include <QStringList>

class TMDbSeriesParser : public JsonScraper
{
public:
    TMDbSeriesParser();
    // Dont call any other function if scrapeSeries() didnt return true before
    bool scrapeSeries(QString seriesName);
    QStringList getSeason(int season, QString language);
    int getAmountSeasons();

private:
    using JsonScraper::parsedObject;
    const QString authentificationKey = "020a07e5192867b0bbae8ffb841498e5";
    const QString tmdbUrl = "https://api.themoviedb.org/3/";
    QString seriesID;
    int amountSeasons;

    bool setSeriesInformation();
};

#endif // TMDBSERIESPARSER_H
