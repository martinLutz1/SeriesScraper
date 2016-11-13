#include "jsonscraper.h"


JsonScraper::JsonScraper()
{

}

bool JsonScraper::scrapeJsonObject(QString requestUrl)
{
    bool scrapingSuccessful = false;
    // Create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // The HTTP request
    QNetworkRequest req(requestUrl);
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // Blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray byteArray = reply->readAll();
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(byteArray, &err);

        if (doc.isObject())
        {
            parsedObject = doc.object();
            scrapingSuccessful = true;
        }
        else {
            qDebug() << "Not found";
        }
    }
    else {
        qDebug() << "Failure" << reply->errorString();
    }
    delete reply;
    return scrapingSuccessful;
}
