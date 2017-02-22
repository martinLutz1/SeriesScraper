#ifndef JSONSCRAPER_H
#define JSONSCRAPER_H

#include <QCoreApplication>
#include <QtNetwork>

class JsonScraper
{
public:
    JsonScraper();

protected:
    bool scrapeJsonObjectViaPost(QString requestUrl, QJsonObject post);
    bool scrapeJsonObjectViaGet(QString requestUrl, QJsonObject headerArguments = QJsonObject());
    QJsonObject parsedObject;

private:
    bool parseReply(QNetworkReply *reply);
};

#endif // JSONSCRAPER_H
