#ifndef SERIESPARSER_H
#define SERIESPARSER_H

#include <QStringList>
#include "omdbseriesparser.h"
#include "tmdbseriesparser.h"

class SeriesParser
{
public:
    SeriesParser();
    void setSeriesParser(int seriesParser);
    int getSeriesParser();
    bool scrapeSeries(QString series);
    QString getSeriesName();
    QString getSeriesYear();
    QString getPosterUrl();
    QString getPlot();
    int getAmountSeasons();
    QStringList getEpisodeList(int season, QString language);
    QString getSeriesInput();

    enum seriesParser{tmdb, omdb};

private:
    OMDbSeriesParser omdbSeriesParser;
    TMDbSeriesParser tmdbSeriesParser;
    int selectedSeriesParser; // 0 = TMDb, 1 = OMDb
    QString seriesInput;
};

#endif // SERIESPARSER_H
