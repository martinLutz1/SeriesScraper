#ifndef SERIESPARSER_H
#define SERIESPARSER_H

#include <QString>
#include <QStringList>

class SeriesParser
{
private:
    QStringList idList;
    int amountSeasons;

public:
    SeriesParser();
    bool getSeriesSeason(QString url, QString series, int season, QString id);

    // Only execute if getIDfromURL returned true before, otherwise you will get an empty string
    QStringList getIDValue();
    int getAmountSeasons();
};

#endif // SERIESPARSER_H
