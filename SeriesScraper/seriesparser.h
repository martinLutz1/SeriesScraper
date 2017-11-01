#ifndef SERIESPARSER_H
#define SERIESPARSER_H

#include <QString>
#include "omdbseriesparser.h"
#include "tmdbseriesparser.h"
#include "tvdbseriesparser.h"

class SeriesParser
{
public:
    SeriesParser();
    ~SeriesParser();
    void setSeriesParser(int selectedSeriesParser);
    void setSeriesInput(QString series);

    BaseSeriesParser *getSeriesParser();
    int getSeriesParserIndex();
    QString getSeriesInput();

public:
    enum seriesParser{tmdb, omdb, tvdb};

private:
    OMDbSeriesParser omdbSeriesParser;
    TMDbSeriesParser tmdbSeriesParser;
    TVDBSeriesParser tvdbSeriesParser;
    BaseSeriesParser *parser;

    int selectedSeriesParser = seriesParser::tmdb;
    QString seriesInput;
};

#endif // SERIESPARSER_H
