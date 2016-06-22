#include "jsonparser.h"
#include <QCoreApplication>
#include <QtNetwork>
#include <QDebug>

JsonParser::JsonParser(QObject *parent) : QObject(parent)
{
    // Avoid SSL-Errors under OSX
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");

}

QString JsonParser::getIDfromURL(QString pUrl, QString id)
{
    // create custom temporary event loop on stack
    QString title = "";
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req(pUrl);
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if(reply->error() == QNetworkReply::NoError) {
        QByteArray byteArray = reply->readAll();
        delete reply;

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(byteArray, &err);
        if(doc.isObject())
        {
            QJsonObject obj = doc.object();
            title = obj.value("Title").toString();
        }

    }
    else {
        //failure
        qDebug() << "Failure" << reply->errorString();
        delete reply;
    }
    return title;
}

