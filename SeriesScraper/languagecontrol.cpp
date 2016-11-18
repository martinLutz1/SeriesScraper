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
}

bool LanguageControl::initialize()
{
    languageFileDirectory.setPath(QCoreApplication::applicationDirPath());
    QStringList fileType("*.json");
    if (!languageFileDirectory.cd("language")) {
        return false;
    }
    else { // Language files exist, load them
        languageFileList = languageFileDirectory.entryInfoList(fileType, QDir::Files);
        if (languageFileList.isEmpty()) {
            return false;
        } else {
            return true;
        }
    }
}

QStringList LanguageControl::getLanguageList()
{
    QStringList languageListWithoutExtensions;
    for (int i = 0; i < languageFileList.size(); i++) {
        languageListWithoutExtensions << languageFileList.at(i).baseName();
    }
    return languageListWithoutExtensions;
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
                        << obj.value("About").toString()
                        << obj.value("Settings").toString()
                        << obj.value("Language").toString()
                        << obj.value("Display").toString()
                        << obj.value("Help").toString()
                        << obj.value("Close").toString()
                        << obj.value("Done").toString()
                        << obj.value("General").toString()
                        << obj.value("Interface").toString()
                        << obj.value("ShowSeriesInformation").toString()
                        << obj.value("SaveOnExit").toString()
                        << obj.value("SeriesDatabase").toString()
                        << obj.value("Recommended").toString()
                        << obj.value("NewFormat").toString()
                        << obj.value("Add").toString()
                        << obj.value("Remove").toString()
                        << obj.value("Video").toString()
                        << obj.value("NewNameScheme").toString()
                        << obj.value("Reset").toString()
                        << obj.value("ResetAll").toString()
                        << obj.value("NotFound").toString()
                        << obj.value("SeriesLanguageNotFound").toString()
                        << obj.value("NameSchemeNotFound").toString()
                        << obj.value("RenameFailed").toString()
                        << obj.value("RenameSuccess").toString();

        languageData.setTranslationSet(translationList);
        languageData.setLanguage(language);
        return true;
    }
    return false;
}

QString LanguageControl::getTranslation(int translateThis)
{
    if (translateThis < languageData.getTranslationList().size())
        return languageData.getTranslation(translateThis);
    else
        return QString("");
}

QStringList LanguageControl::getTranslationList()
{
    return languageData.getTranslationList();
}

