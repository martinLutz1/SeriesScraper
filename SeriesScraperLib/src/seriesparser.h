#ifndef SERIESPARSER_H
#define SERIESPARSER_H

#include <QString>
#include "omdbseriesparser.h"
#include "tmdbseriesparser.h"
#include "tvdbseriesparser.h"

class SeriesParser
{
public:
    enum class Parser { tmdb, omdb, tvdb };

public:
    SeriesParser();
    ~SeriesParser();
    void setSeriesParser(Parser selectedSeriesParser);
    void setSeriesInput(QString series);

    BaseSeriesParser *getSeriesParser();
    SeriesParser::Parser getSeriesParserIndex();
    QString getSeriesInput();

private:
    OMDbSeriesParser omdbSeriesParser;
    TMDbSeriesParser tmdbSeriesParser;
    TVDBSeriesParser tvdbSeriesParser;
    BaseSeriesParser *parser;

    Parser selectedSeriesParser = Parser::tmdb;
    QString seriesInput;
};

#endif // SERIESPARSER_H
