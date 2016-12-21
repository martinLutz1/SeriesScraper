#include "omdbseriesparser.h"
#include <QCoreApplication>
#include <QtNetwork>
#include <QDebug>

OMDbSeriesParser::OMDbSeriesParser()
{
    // Avoid SSL-Errors under OSX
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
}

bool OMDbSeriesParser::scrapeSeries(QString series)
{
    seriesFullName.clear();
    amountSeasons = 0;
    year.clear();

    if (series.isEmpty())
        return false;

    QString requestUrl = "http://www.omdbapi.com/?t=" + series + "&r=json";
    bool scrapingSuccessful = scrapeJsonObject(requestUrl);
    if (scrapingSuccessful)
    {
        amountSeasons = parsedObject.value("totalSeasons").toString().toInt();
        seriesFullName = parsedObject.value("Title").toString();
        posterUrl = parsedObject.value("Poster").toString();
        plot = parsedObject.value("Plot").toString();

        scrapingSuccessful = !seriesFullName.isEmpty();
    }
    return scrapingSuccessful;
}

QStringList OMDbSeriesParser::getSeason(int season, QString language)
{
    QStringList episodeList;
    QString requestUrl = "http://www.omdbapi.com/?t=" + seriesFullName + "&season=" + QString::number(season);

    bool scrapingSuccessful = scrapeJsonObject(requestUrl);
    if (scrapingSuccessful)
    {
        QJsonArray episodeArray = parsedObject.value("Episodes").toArray();
        for (int i = 0; i < episodeArray.size(); i++)
            episodeList << episodeArray[i].toObject().value("Title").toString();
        if (!episodeArray.isEmpty())
            year = episodeArray[0].toObject().value("Released").toString().left(4);
    }
    return episodeList;
}

