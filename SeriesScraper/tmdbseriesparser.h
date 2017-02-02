#ifndef TMDBSERIESPARSER_H
#define TMDBSERIESPARSER_H

#include "baseseriesparser.h"
#include <QStringList>

class TMDbSeriesParser : public BaseSeriesParser
{
public:
    TMDbSeriesParser();
    bool scrapeSeries(QString series);
    QStringList getSeason(int season, QString language);

private:
    const QString authentificationKey = "020a07e5192867b0bbae8ffb841498e5";
    const QString tmdbUrl = "http://api.themoviedb.org/3/";
    const QString basePosterUrl = "http://image.tmdb.org/t/p/w780";
    QString seriesID = "";
    QString lastScrapedSeries = "";

    bool setSeriesInformation(QString seasonNumberText);
    bool setAmountSeasons();
};

#endif // TMDBSERIESPARSER_H
