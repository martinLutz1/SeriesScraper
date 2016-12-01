#ifndef JSONSCRAPER_H
#define JSONSCRAPER_H

#include <QCoreApplication>
#include <QtNetwork>

class JsonScraper
{
public:
    JsonScraper();

protected:
    bool scrapeJsonObject(QString requestUrl);
    QJsonObject parsedObject;
};

#endif // JSONSCRAPER_H
