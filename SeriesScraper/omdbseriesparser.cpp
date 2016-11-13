#include "omdbseriesparser.h"
#include <QCoreApplication>
#include <QtNetwork>
#include <QDebug>

OMDbSeriesParser::OMDbSeriesParser()
{
    // Avoid SSL-Errors under OSX
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
}

bool OMDbSeriesParser::getSeriesSeason(QString url, QString series, int season, QString id)
{
    // Create request string
    QString requestUrl = url  + "t=" + series + "&season=" + QString::number(season);

    // Create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // The HTTP request
    QNetworkRequest req(requestUrl);
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // Blocks stack until "finished()" has been called

    if(reply->error() == QNetworkReply::NoError) {
        QByteArray byteArray = reply->readAll();
        delete reply;

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(byteArray, &err);
        QStringList values;
        if(doc.isObject())
        {
            QJsonObject obj = doc.object();
            QJsonArray array = obj.value("Episodes").toArray();
            for (int i = 0; i < array.size(); i++)
                values << array[i].toObject().value(id).toString();

            amountSeasons = obj.value("totalSeasons").toString().toInt();
            idList = values;
            return !array.isEmpty(); // True if we got any elements
        }
    }
    else {
        qDebug() << "Failure" << reply->errorString();
        delete reply;
    }
    return false;
}

QStringList OMDbSeriesParser::getIDValue()
{
    return idList;
}

int OMDbSeriesParser::getAmountSeasons()
{
    return amountSeasons;
}

