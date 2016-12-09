#ifndef LANGUAGERHANDLER_H
#define LANGUAGERHANDLER_H

#include "languagedata.h"
#include "jsonloader.h"
#include <QDir>


class LanguageHandler : public JsonLoader
{
private:
   LanguageData languageData;
   QDir languageFileDirectory;
   QFileInfoList languageFileList;

public:
    LanguageHandler();
    bool initialize();
    QStringList getLanguageList();
    bool loadLanguage(QString language);
    QString getTranslation(int translateThis);
    QStringList getTranslationList();
};

#endif // LANGUAGERHANDLER_H
