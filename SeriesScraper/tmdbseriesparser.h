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
    QString getYear();

private:
    const QString authentificationKey = "020a07e5192867b0bbae8ffb841498e5";
    const QString tmdbUrl = "http://api.themoviedb.org/3/";
    QString seriesID;

    bool setSeriesInformation(QString language);
    QString getYear(QString firstAirDate, QString lastAirDate);
};

#endif // TMDBSERIESPARSER_H
