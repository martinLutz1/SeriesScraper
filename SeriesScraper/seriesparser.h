#ifndef SERIESPARSER_H
#define SERIESPARSER_H

#include <QStringList>
#include <vector>
#include "omdbseriesparser.h"
#include "tmdbseriesparser.h"
#include "tvdbseriesparser.h"

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

    enum seriesParser{tmdb, omdb, tvdb};

private:
    OMDbSeriesParser omdbSeriesParser;
    TMDbSeriesParser tmdbSeriesParser;
    TVDBSeriesParser tvdbSeriesParser;
    std::vector<BaseSeriesParser*> seriesParserVector;

    int selectedSeriesParser; // 0 = TMDb, 1 = OMDb, 2 = TVDB
    QString seriesInput;
};

#endif // SERIESPARSER_H
