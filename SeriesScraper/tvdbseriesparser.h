#ifndef TVDBSERIESPARSER_H
#define TVDBSERIESPARSER_H

#include "baseseriesparser.h"
#include <QStringList>
#include <QByteArray>

class TVDBSeriesParser : public BaseSeriesParser
{
public:
    TVDBSeriesParser();
    bool scrapeSeries(QString series);
    QStringList getSeason(int season, QString language);
    bool downloadPoster();


private:
    const QString apiKey = "99DBAA5F3B8BB8B7";
    const QString userName = "m.lutz";
    const QString userKey = "E6FAA2402891836F";
    const QString baseUrl = "https://api.thetvdb.com/";
    const QString posterBaseUrl = "http://thetvdb.com/banners/posters/";

    QString seriesID;
    QString currentLanguage;
    QString authToken;
    bool loggedIn = false;
    QByteArray poster;

    bool authenticate();
    bool setAmountSeasons();
};

#endif // TVDBSERIESPARSER_H
