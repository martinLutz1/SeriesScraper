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
    seriesID.clear();
    seriesFullName.clear();
    amountSeasons = 0;

    if (series.isEmpty())
        return false;

    QString searchFor = series.replace(" ", "+");
    // Create request string
    QString requestUrl = tmdbUrl  + "search/tv?api_key=" + authentificationKey + "&query=" + searchFor;

    // Get JsonObject from requestUrl;
    bool scrapingSuccessful = scrapeJsonObject(requestUrl);
    if (scrapingSuccessful)
    {
        QJsonArray jsonArray = parsedObject.value("results").toArray();
        if (jsonArray.size() > 0)
        {
            seriesID = QString::number(jsonArray[0].toObject().value("id").toInt());
            bool seriesInformationSet = setSeriesInformation("en-EN");
            if (seriesInformationSet)
                return true;
        }
    }
    return false;
}

QStringList TMDbSeriesParser::getSeason(int season, QString language)
{
    QStringList episodeList;
    QString seasonNumberText = QString("season/").append(QString::number(season));
    QString requestUrl = tmdbUrl  + "tv/" + seriesID + "?api_key=" + authentificationKey + "&language="
            + language + "&append_to_response=" + seasonNumberText;

    bool scrapingSuccessful = scrapeJsonObject(requestUrl);
    if (scrapingSuccessful)
    {
        QJsonArray episodeJsonArray = parsedObject.value(seasonNumberText).toObject().value("episodes").toArray();
        for (int i = 0; i < episodeJsonArray.size(); i++)
            episodeList << episodeJsonArray[i].toObject().value("name").toString();

        // Set year information
        year = parsedObject.value(seasonNumberText).toObject().value("air_date").toString().left(4);

        // Update series name (language may be changed)
        seriesFullName = parsedObject.value("name").toString();
    }
    return episodeList;
}

bool TMDbSeriesParser::setSeriesInformation(QString language)
{
    QString requestUrl = tmdbUrl  + "tv/" + seriesID + "?api_key=" + authentificationKey + "&language=" + language;
    bool scrapingSuccessful = scrapeJsonObject(requestUrl);
    if (scrapingSuccessful)
    {
        QJsonValue numberOfSeasons = parsedObject.value("number_of_seasons");
        QJsonValue seriesName = parsedObject.value("name");
        QJsonValue posterUrlValue = parsedObject.value("poster_path");
        QJsonValue plotValue = parsedObject.value("overview");

        if (numberOfSeasons.isUndefined()
                || seriesName.isUndefined()
                || posterUrlValue.isUndefined()
                || plotValue.isUndefined())
        {
            return false;
        }
        else
        {
            amountSeasons = numberOfSeasons.toInt();
            seriesFullName = seriesName.toString();
            posterUrl = basePosterUrl + posterUrlValue.toString();
            plot = plotValue.toString();
            return true;
        }
    }
    else
        return false;
}
