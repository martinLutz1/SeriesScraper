#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

class JsonLoader
{
public:
    JsonLoader();
    bool loadJsonObject(QString pathToJsonFile);

protected:
    QJsonObject loadedObject;
};

#endif // JSONLOADER_H
