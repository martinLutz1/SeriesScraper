#ifndef INTERFACELANGUAGEHANDLER_H
#define INTERFACELANGUAGEHANDLER_H

#include "languagedata.h"
#include "jsonloader.h"
#include <QDir>


class InterfaceLanguageHandler : public JsonLoader
{
private:
   LanguageData languageData;
   QDir languageFileDirectory;
   QFileInfoList languageFileList;

public:
    InterfaceLanguageHandler();
    bool initialize();
    QStringList getLanguageList();
    bool loadLanguage(QString language);
    QString getTranslation(int translateThis);
    QStringList getTranslationList();
};

#endif // INTERFACELANGUAGEHANDLER_H
