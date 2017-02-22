#include "tmdbseriesparser.h"

#include <QCoreApplication>
#include <QtNetwork>

TMDbSeriesParser::TMDbSeriesParser()
{
    // Avoid SSL-Errors under OSX
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
}

bool TMDbSeriesParser::scrapeSeries(QString series)
{
    QString searchFor = series.replace(" ", "+");
    if (lastScrapedSeries == searchFor)
    {
        return true;
    }

    seriesID.clear();
    seriesFullName.clear();
    amountSeasons = 0;

    if (series.isEmpty())
        return false;

    // Create request string
    QString requestUrl = tmdbUrl  + "search/tv?api_key=" + authentificationKey + "&query=" + searchFor;

    // Get JsonObject from requestUrl;
    bool scrapingSuccessful = scrapeJsonObjectViaGet(requestUrl);
    if (scrapingSuccessful)
    {
        QJsonArray jsonArray = parsedObject.value("results").toArray();
        scrapingSuccessful = !jsonArray.isEmpty();

        if (jsonArray.size() > 0)
        {
            seriesID = QString::number(jsonArray[0].toObject().value("id").toInt());
            setAmountSeasons();
            lastScrapedSeries = searchFor;
        }
    }
    return scrapingSuccessful;
}

QStringList TMDbSeriesParser::getSeason(int season, QString language)
{
    QStringList episodeList;
    QString seasonNumberText = QString("season/").append(QString::number(season));
    QString requestUrl = tmdbUrl  + "tv/" + seriesID + "?api_key=" + authentificationKey + "&language="
            + language + "&append_to_response=" + seasonNumberText;

    bool scrapingSuccessful = scrapeJsonObjectViaGet(requestUrl);
    if (scrapingSuccessful)
    {
        QJsonArray episodeJsonArray = parsedObject.value(seasonNumberText).toObject().value("episodes").toArray();
        for (int i = 0; i < episodeJsonArray.size(); i++)
        {
            episodeList << episodeJsonArray[i].toObject().value("name").toString();
        }
        setSeriesInformation(seasonNumberText);
    }
    return episodeList;
}

bool TMDbSeriesParser::setSeriesInformation(QString seasonNumberText)
{
    QJsonValue yearValue = parsedObject.value(seasonNumberText).toObject().value("air_date");
    QJsonValue seriesFullNameValue = parsedObject.value("name");
    QJsonValue posterUrlValue = parsedObject.value(seasonNumberText).toObject().value("poster_path");
    QJsonValue plotValue = parsedObject.value(seasonNumberText).toObject().value("overview");

    if (yearValue.isUndefined()
            || seriesFullNameValue.isUndefined()
            || posterUrlValue.isUndefined()
            || plotValue.isUndefined())
    {
        year = "";
        amountSeasons = 0;
        seriesFullName = "";
        posterUrl = "";
        plot = "";
        return false;
    } else
    {
        year = yearValue.toString().left(4);
        seriesFullName = seriesFullNameValue.toString();
        if (!posterUrlValue.toString().isEmpty())
        {
            posterUrl = basePosterUrl + posterUrlValue.toString();
        }
        else
        {
            posterUrl.clear();
        }
        plot = plotValue.toString();
        return true;
    }
}

bool TMDbSeriesParser::setAmountSeasons()
{
    QString requestUrl = tmdbUrl  + "tv/" + seriesID + "?api_key=" + authentificationKey + "&language=english";
    bool scrapingSuccessful = scrapeJsonObjectViaGet(requestUrl);
    if (scrapingSuccessful)
    {
         QJsonValue amountSeasonsValue = parsedObject.value("number_of_seasons");
         if (amountSeasonsValue.isUndefined())
         {
             amountSeasons = 0;
             return false;
         } else
         {
             amountSeasons = amountSeasonsValue.toInt();
             return true;
         }
    }
    return false;
}
