#include "jsonscraper.h"


JsonScraper::JsonScraper()
{

}

bool JsonScraper::scrapeJsonObjectViaPost(QString requestUrl, QJsonObject post)
{
    // Create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // The HTTP request
    QNetworkRequest req(requestUrl);
    QString applicationJson = "application/json";
    req.setHeader(QNetworkRequest::ContentTypeHeader, applicationJson.toLocal8Bit());
    req.setRawHeader("Accept", applicationJson.toLocal8Bit());

    QNetworkReply *reply = mgr.post(req, QJsonDocument(post).toJson());

    eventLoop.exec(); // Blocks stack until "finished()" has been called
    return parseReply(reply);
}

bool JsonScraper::scrapeJsonObjectViaGet(QString requestUrl, QJsonObject headerArguments)
{
    // Create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // The HTTP request
    QNetworkRequest req(requestUrl);

    while (!headerArguments.isEmpty())
    {
        QString headerName = headerArguments.keys().at(0);
        QString headerValue = headerArguments.take(headerName).toString();
        req.setRawHeader(headerName.toLocal8Bit(), headerValue.toLocal8Bit());
    }

    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // Blocks stack until "finished()" has been called
    return parseReply(reply);
}

bool JsonScraper::parseReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray byteArray = reply->readAll();
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(byteArray, &err);

        if (doc.isObject())
        {
            parsedObject = doc.object();
            return true;
        } else
        {
            qDebug() << "Not found";
            return false;
        }
    } else
    {
        qDebug() << "Failure" << reply->errorString();
        return false;
    }
}
