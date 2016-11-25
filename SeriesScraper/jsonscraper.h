#ifndef JSONSCRAPER_H
#define JSONSCRAPER_H

#include <QCoreApplication>
#include <QtNetwork>

class JsonScraper
{
public:
    JsonScraper();
    bool scrapeJsonObject(QString requestUrl);

protected:
    QJsonObject parsedObject;
};

#endif // JSONSCRAPER_H
