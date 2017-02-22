#include "tvdbseriesparser.h"

TVDBSeriesParser::TVDBSeriesParser()
{
}

bool TVDBSeriesParser::scrapeSeries(QString series)
{
    if (lastScrapedSeries == series)
        return true;

    seriesID.clear();
    seriesFullName.clear();
    amountSeasons = 0;

    if (series.isEmpty())
        return false;

    if (!loggedIn)
        loggedIn = authenticate();

    QString requestUrl = baseUrl + "search/series?name=" + series;
    QJsonObject headerArguments;
    headerArguments.insert("Authorization", authToken);

    bool scrapingSuccessful = scrapeJsonObjectViaGet(requestUrl, headerArguments);
    if (scrapingSuccessful)
    {
        QJsonArray seriesArray = parsedObject.value("data").toArray();
        scrapingSuccessful = !seriesArray.isEmpty();

        if (scrapingSuccessful)
        {
            seriesID = QString::number(seriesArray.at(0).toObject().value("id").toInt());
            seriesFullName = seriesArray.at(0).toObject().value("seriesName").toString();
            plot = seriesArray.at(0).toObject().value("overview").toString();
            lastScrapedSeries = series;
            setAmountSeasons();
            posterUrl = posterBaseUrl + seriesID + "-1.jpg";
        }
    }
    return scrapingSuccessful;
}

QStringList TVDBSeriesParser::getSeason(int season, QString language)
{
    QStringList episodeList;
    QString requestUrl = baseUrl + "series/" + seriesID + "/episodes/query?airedSeason=" + QString::number(season);
    QJsonObject headerArguments;
    headerArguments.insert("Authorization", authToken);
    headerArguments.insert("Accept-Language", language);

    bool scrapingSuccessful = scrapeJsonObjectViaGet(requestUrl, headerArguments);
    if (scrapingSuccessful)
    {
        QJsonArray episodeArray = parsedObject.value("data").toArray();
        for (int i = 0; i < episodeArray.size(); i++)
        {
            episodeList << episodeArray.at(i).toObject().value("episodeName").toString();
        }
        year = episodeArray.at(0).toObject().value("firstAired").toString().left(4);
    }
    return episodeList;
}

bool TVDBSeriesParser::authenticate()
{
    QJsonObject postData;
    postData.insert("apikey", apiKey);
    postData.insert("username", userName);
    postData.insert("userkey", userKey);

    bool scrapingSuccessful = scrapeJsonObjectViaPost(baseUrl + "login", postData);
    if (scrapingSuccessful)
    {
        authToken = "Bearer " + parsedObject.value("token").toString();
    }
    return scrapingSuccessful;
}

bool TVDBSeriesParser::setAmountSeasons()
{
    QString requestUrl = baseUrl + "series/" + seriesID + "/episodes/summary";
    QJsonObject headerArguments;
    headerArguments.insert("Authorization", authToken);

    bool scrapingSuccessful = scrapeJsonObjectViaGet(requestUrl, headerArguments);
    if (scrapingSuccessful)
    {
        QJsonArray seasonArray = parsedObject.value("data").toObject().value("airedSeasons").toArray();
        scrapingSuccessful = !seasonArray.isEmpty();

        int newAmountSeasons = 0;
        for (int i = 0; i < seasonArray.size(); i++)
            newAmountSeasons = std::max(newAmountSeasons, seasonArray.at(i).toString().toInt());

        amountSeasons = newAmountSeasons;
    }
    return scrapingSuccessful;
}
