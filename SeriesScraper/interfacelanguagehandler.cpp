#include "interfacelanguagehandler.h"
#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIODevice>

InterfaceLanguageHandler::InterfaceLanguageHandler()
{
}

bool InterfaceLanguageHandler::initialize()
{
    bool languageFilesExist = false;
    languageFileDirectory.setPath(QCoreApplication::applicationDirPath());
    QStringList fileType("*.json");

    if (languageFileDirectory.cd("language"))
    {
        languageFileList = languageFileDirectory.entryInfoList(fileType, QDir::Files);
        if (!(languageFileList.isEmpty()))
            languageFilesExist = true;
    }
    return languageFilesExist;
}

QStringList InterfaceLanguageHandler::getLanguageList()
{
    QStringList languageListWithoutExtensions;
    for (int i = 0; i < languageFileList.size(); i++)
        languageListWithoutExtensions << languageFileList.at(i).baseName();

    return languageListWithoutExtensions;
}

bool InterfaceLanguageHandler::loadLanguage(QString language)
{
    QString filePath =  languageFileDirectory.absoluteFilePath(language.append(".json"));
    bool loadingSuccessful = loadJsonObject(filePath);

    if(loadingSuccessful)
    {
        QStringList translationList;
        translationList << loadedObject.value("OldNames").toString()
                        << loadedObject.value("NewNames").toString()
                        << loadedObject.value("DirectorySelection").toString()
                        << loadedObject.value("Selection").toString()
                        << loadedObject.value("Path").toString()
                        << loadedObject.value("SeriesSelection").toString()
                        << loadedObject.value("Series").toString()
                        << loadedObject.value("SeriesInfo").toString()
                        << loadedObject.value("EpisodeNumber").toString()
                        << loadedObject.value("AirDate").toString()
                        << loadedObject.value("Season").toString()
                        << loadedObject.value("NameScheme").toString()
                        << loadedObject.value("Rename").toString()
                        << loadedObject.value("ForceRename").toString()
                        << loadedObject.value("About").toString()
                        << loadedObject.value("Settings").toString()
                        << loadedObject.value("FullScreen").toString()
                        << loadedObject.value("Language").toString()
                        << loadedObject.value("Display").toString()
                        << loadedObject.value("Help").toString()
                        << loadedObject.value("Close").toString()
                        << loadedObject.value("Done").toString()
                        << loadedObject.value("Yes").toString()
                        << loadedObject.value("No").toString()
                        << loadedObject.value("AreYouSure").toString()
                        << loadedObject.value("AreYouSureDetailed").toString()
                        << loadedObject.value("General").toString()
                        << loadedObject.value("Interface").toString()
                        << loadedObject.value("DarkTheme").toString()
                        << loadedObject.value("ShowSeriesInformation").toString()
                        << loadedObject.value("SaveOnExit").toString()
                        << loadedObject.value("SeriesDatabase").toString()
                        << loadedObject.value("Recommended").toString()
                        << loadedObject.value("NewFormat").toString()
                        << loadedObject.value("Add").toString()
                        << loadedObject.value("Remove").toString()
                        << loadedObject.value("Video").toString()
                        << loadedObject.value("NewNameScheme").toString()
                        << loadedObject.value("Reset").toString()
                        << loadedObject.value("ResetAll").toString()
                        << loadedObject.value("NotFound").toString()
                        << loadedObject.value("SeriesLanguageNotFound").toString()
                        << loadedObject.value("NameSchemeFileNotFound").toString()
                        << loadedObject.value("NameSchemeLineNotFound").toString()
                        << loadedObject.value("RenameFailed").toString()
                        << loadedObject.value("RenameSuccess").toString();

        languageData.setTranslationSet(translationList);
        languageData.setLanguage(language);
    }
    return loadingSuccessful;
}

QString InterfaceLanguageHandler::getTranslation(int translateThis)
{
    if (translateThis < languageData.getTranslationList().size())
        return languageData.getTranslation(translateThis);
    else
        return QString("");
}

QStringList InterfaceLanguageHandler::getTranslationList()
{
    return languageData.getTranslationList();
}

