#include "tvdbseriesparser.h"

TVDBSeriesParser::TVDBSeriesParser()
{

}

bool TVDBSeriesParser::scrapeSeries(QString series)
{
    if (!loggedIn)
    {
        loggedIn = authenticate();
        qDebug() << authToken;
    }
    return true;
    if (lastScrapedSeries == series)
    {
        return true;
    }

    //bool scrapingSuccessful = scrapeJsonObject("requestUrl", postData, authorizationKey);
    return true;
}

QStringList TVDBSeriesParser::getSeason(int season, QString language)
{
    return QStringList();
}

bool TVDBSeriesParser::authenticate()
{
    QJsonObject postData;
    postData.insert("apikey", apiKey);
    postData.insert("username", userName);
    postData.insert("userkey", userKey);

    bool scrapingSuccessful = scrapeJsonObjectViaPost(loginUrl, postData);
    if (scrapingSuccessful)
    {
        authToken = "Bearer " + parsedObject.value("token").toString();
    }
    return scrapingSuccessful;
}
