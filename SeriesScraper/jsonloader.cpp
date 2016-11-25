#include "jsonloader.h"

JsonLoader::JsonLoader()
{

}

bool JsonLoader::loadJsonObject(QString pathToJsonFile)
{
    QFile loadFile(pathToJsonFile);

    if (!loadFile.open(QIODevice::ReadOnly))
        return false;

    QByteArray byteArray = loadFile.readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(byteArray, &err);
    loadFile.close();

    if (doc.isObject())
    {
        loadedObject = doc.object();
        return true;
    } else
    {
        return false;
    }
}
