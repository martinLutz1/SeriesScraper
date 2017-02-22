#ifndef TVDBSERIESPARSER_H
#define TVDBSERIESPARSER_H

#include "baseseriesparser.h"
#include <QStringList>

class TVDBSeriesParser : public BaseSeriesParser
{
public:
    TVDBSeriesParser();
    bool scrapeSeries(QString series);
    QStringList getSeason(int season, QString language);

private:
    const QString apiKey = "99DBAA5F3B8BB8B7";
    const QString userName = "m.lutz";
    const QString userKey = "E6FAA2402891836F";
    const QString loginUrl = "https://api.thetvdb.com/login";

    QString authToken;
    bool loggedIn = false;

    bool authenticate();
};

#endif // TVDBSERIESPARSER_H
