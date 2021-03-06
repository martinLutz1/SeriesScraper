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
    if (lastScrapedSeries == series)
    {
        return true;
    }

    seriesFullName.clear();
    year.clear();
    lastScrapedSeries.clear();
    amountSeasons = 0;

    if (series.isEmpty())
    {
        return false;
    }

    QString requestUrl = baseUrl + series + "&r=json";
    bool scrapingSuccessful = scrapeJsonObjectViaGet(requestUrl);
    if (scrapingSuccessful)
    {
        amountSeasons = parsedObject.value("totalSeasons").toString().toInt();
        seriesFullName = parsedObject.value("Title").toString();
        posterUrl = parsedObject.value("Poster").toString();
        plot = parsedObject.value("Plot").toString();
        scrapingSuccessful = !seriesFullName.isEmpty() && (amountSeasons > 0);
        lastScrapedSeries = series;
    }
    return scrapingSuccessful;
}

QStringList OMDbSeriesParser::getSeason(int season, QString language /* unused */)
{   
    Q_UNUSED(language);
    QStringList episodeList;
    QString requestUrl = baseUrl + seriesFullName + "&season=" + QString::number(season);

    bool scrapingSuccessful = scrapeJsonObjectViaGet(requestUrl);
    if (scrapingSuccessful)
    {
        QJsonArray episodeArray = parsedObject.value("Episodes").toArray();
        for (int i = 0; i < episodeArray.size(); i++)
        {
            episodeList << episodeArray[i].toObject().value("Title").toString();
        }
        if (!episodeArray.isEmpty())
        {
            year = episodeArray[0].toObject().value("Released").toString().left(4);
        }
    }
    return episodeList;
}
