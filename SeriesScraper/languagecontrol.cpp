#include "languagecontrol.h"
#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIODevice>

LanguageControl::LanguageControl()
{
    languageFileDirectory.setPath(QCoreApplication::applicationDirPath());
    if (!languageFileDirectory.cd("language"))
        qWarning("Language directory not found"); // output on statuslabel
}

bool LanguageControl::loadLanguage(QString language)
{
    QString fileName =  languageFileDirectory.absoluteFilePath(language.append(".json"));
    QFile loadFile(fileName);

    if (!loadFile.open(QIODevice::ReadOnly))
        return false;

    QByteArray languageByteArray = loadFile.readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(languageByteArray, &err);

    if(doc.isObject())
    {
        QJsonObject obj = doc.object();
        QStringList translationList;
        translationList << obj.value("OldNames").toString()
                        << obj.value("NewNames").toString()
                        << obj.value("DirectorySelection").toString()
                        << obj.value("Selection").toString()
                        << obj.value("Path").toString()
                        << obj.value("SeriesSelection").toString()
                        << obj.value("Series").toString()
                        << obj.value("Season").toString()
                        << obj.value("NameScheme").toString()
                        << obj.value("Rename").toString()
                        << obj.value("Settings").toString()
                        << obj.value("Language").toString()
                        << obj.value("NotFound").toString();

        languageData.setTranslationSet(translationList);
        languageData.setLanguage(language);

        return true;
    }
    return false;
}

QString LanguageControl::getTranslation(int translateThis)
{
    languageData.getTranslation(translateThis);
}

QStringList LanguageControl::getTranslationList()
{
    return languageData.getTranslationList();
}

