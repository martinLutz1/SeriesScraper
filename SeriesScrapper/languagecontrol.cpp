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
        qWarning("Language directory not found");
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
        translationList << obj.value("DirectorySelection").toString()
                        << obj.value("Episode").toString()
                        << obj.value("EpisodeName").toString()
                        << obj.value("FileName").toString()
                        << obj.value("Path").toString()
                        << obj.value("Season").toString()
                        << obj.value("Selection").toString()
                        << obj.value("Series").toString()
                        << obj.value("SeriesSelection").toString();


        languageData.setDirectorySelection(translationList.at(0));
        languageData.setEpisode(translationList.at(1));
        languageData.setEpisodeName(translationList.at(2));
        languageData.setFileName(translationList.at(3));
        languageData.setPath(translationList.at(4));
        languageData.setSeason(translationList.at(5));
        languageData.setSelection(translationList.at(6));
        languageData.setSeries(translationList.at(7));
        languageData.setSeriesSelection(translationList.at(8));

        return true;
    }
    return false;

}

QString LanguageControl::getEpisodeName()
{
    return languageData.getEpisodeName();
}

QString LanguageControl::getFileName()
{
    return languageData.getFileName();
}

QString LanguageControl::getDirectorySelection()
{
    return languageData.getDirectorySelection();
}

QString LanguageControl::getPath()
{
    return languageData.getPath();
}

QString LanguageControl::getSelection()
{
    return languageData.getSelection();
}

QString LanguageControl::getSeries()
{
    return languageData.getSeries();
}

QString LanguageControl::getSeriesSelection()
{
    return languageData.getSeriesSelection();
}

QString LanguageControl::getSeason()
{
    return languageData.getSeriesSelection();
}

QString LanguageControl::getEpisode()
{
    return languageData.getEpisode();
}
