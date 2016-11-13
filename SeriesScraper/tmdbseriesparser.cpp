#include "tmdbseriesparser.h"

#include <QCoreApplication>
#include <QtNetwork>

TMDbSeriesParser::TMDbSeriesParser()
{
    // Avoid SSL-Errors under OSX
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
}

bool TMDbSeriesParser::scrapeSeries(QString seriesName)
{
    seriesID.clear();
    amountSeasons = 0;

    QString searchFor = seriesName.replace(" ", "+");
    // Create request string
    QString requestUrl = tmdbUrl  + "search/tv?api_key=" + authentificationKey + "&query=" + searchFor;

    // Get JsonObject from requestUrl;
    bool scrapingSuccessful = scrapeJsonObject(requestUrl);
    if (scrapingSuccessful) {
        QJsonArray jsonArray = parsedObject.value("results").toArray();
        if (jsonArray.size() > 0) {
            seriesID = QString::number(jsonArray[0].toObject().value("id").toInt());
            bool seriesInformationSet = setSeriesInformation();
            if (seriesInformationSet) {
                return true;
            }
        }
    }
    return false;
}

QStringList TMDbSeriesParser::getSeason(int season, QString language)
{
    QStringList episodeList;
    QString requestUrl = tmdbUrl  + "tv/" + seriesID + "/season/" + QString::number(season) + "?api_key=" + authentificationKey + "&language="
            + language;
    bool scrapingSuccessful = scrapeJsonObject(requestUrl);
    if (scrapingSuccessful) {
        QJsonArray jsonArray = parsedObject.value("episodes").toArray();
        for (int i = 0; i < jsonArray.size(); i++) {
            episodeList << jsonArray[i].toObject().value("name").toString();
        }
    }
    return episodeList;
}

int TMDbSeriesParser::getAmountSeasons()
{
    return amountSeasons;
}


bool TMDbSeriesParser::setSeriesInformation()
{
    QString requestUrl = tmdbUrl  + "tv/" + seriesID + "?api_key=" + authentificationKey;
    bool scrapingSuccessful = scrapeJsonObject(requestUrl);
    if (scrapingSuccessful) {
        QJsonValue numberOfSeasons = parsedObject.value("number_of_seasons");

        if (numberOfSeasons.isUndefined()) {
            return false;
        }
        else {
            amountSeasons = numberOfSeasons.toInt();
            return true;
        }
    }
    else {
        return false;
    }
}
