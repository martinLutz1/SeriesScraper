#ifndef TMDBSERIESPARSER_H
#define TMDBSERIESPARSER_H

#include "jsonscraper.h"
#include <QStringList>

class TMDbSeriesParser : public JsonScraper
{
public:
    TMDbSeriesParser();
    bool scrapeSeries(QString series);
    QStringList getSeason(int season, QString language);
    int getAmountSeasons();
    QString getYear();
    QString getSeriesName();

private:
    const QString authentificationKey = "020a07e5192867b0bbae8ffb841498e5";
    const QString tmdbUrl = "http://api.themoviedb.org/3/";

    QString seriesID;
    QString seriesFullName;
    QString year;
    int amountSeasons;

    bool setSeriesInformation(QString language);
    QString getYear(QString firstAirDate, QString lastAirDate);
};

#endif // TMDBSERIESPARSER_H
