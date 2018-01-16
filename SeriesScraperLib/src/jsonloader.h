#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

class JsonLoader
{
public:
    JsonLoader();

protected:
    bool loadJsonObject(QString pathToJsonFile);
    QJsonObject loadedObject;
};

#endif // JSONLOADER_H
