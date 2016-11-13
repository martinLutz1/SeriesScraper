#ifndef OMDBSERIESPARSER_H
#define OMDBSERIESPARSER_H

#include <QStringList>

class OMDbSeriesParser
{
private:
    QStringList idList;
    int amountSeasons;

public:
    OMDbSeriesParser();
    bool getSeriesSeason(QString url, QString series, int season, QString id);

    // Only execute if getIDfromURL returned true before, otherwise you will get an empty string
    QStringList getIDValue();
    int getAmountSeasons();
};

#endif // OMDBSERIESPARSER_H
