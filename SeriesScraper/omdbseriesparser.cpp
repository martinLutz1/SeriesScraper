#include "omdbseriesparser.h"
#include <QCoreApplication>
#include <QtNetwork>
#include <QDebug>

OMDbSeriesParser::OMDbSeriesParser()
{
    // Avoid SSL-Errors under OSX
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
}

bool OMDbSeriesParser::scrapeSeries(QString series, int season)
{
    bool scrapingSuccessful = false;
    // Create request string
    QString requestUrl = "http://www.omdbapi.com/?t=" + series + "&season=" + QString::number(season);

    if (scrapeJsonObject(requestUrl))
    {
        amountSeasons = parsedObject.value("totalSeasons").toString().toInt();
        QStringList episodes;
        QJsonArray episodeArray = parsedObject.value("Episodes").toArray();
        for (int i = 0; i < episodeArray.size(); i++)
            episodes << episodeArray[i].toObject().value("Title").toString();
        episodeList = episodes;

        scrapingSuccessful = !episodeArray.isEmpty(); // True if we got any elements
    }
    return scrapingSuccessful;
}

QStringList OMDbSeriesParser::getEpisodeList()
{
    return episodeList;
}

int OMDbSeriesParser::getAmountSeasons()
{
    return amountSeasons;
}

