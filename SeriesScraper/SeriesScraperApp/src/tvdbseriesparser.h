#ifndef TVDBSERIESPARSER_H
#define TVDBSERIESPARSER_H

#include "baseseriesparser.h"
#include <QStringList>

class TVDBSeriesParser : public BaseSeriesParser
{
public:
    TVDBSeriesParser();
    bool scrapeSeries(QString series) override;
    QStringList getSeason(int season, QString language) override;

private:
    const QString apiKey = "99DBAA5F3B8BB8B7";
    const QString userName = "m.lutz";
    const QString userKey = "E6FAA2402891836F";
    const QString baseUrl = "https://api.thetvdb.com/";
    const QString posterBaseUrl = "https://www.thetvdb.com/banners/";

    QString seriesID;
    QString currentLanguage;
    QString authToken;
    bool loggedIn = false;

    bool authenticate();
    bool setAmountSeasons();
    bool setPosterUrl();
};

#endif // TVDBSERIESPARSER_H
