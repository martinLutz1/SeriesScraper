#ifndef LANGUAGECONTROL_H
#define LANGUAGECONTROL_H

#include "languagedata.h"
#include <QDir>


class LanguageControl
{
private:
   LanguageData languageData;
   QDir languageFileDirectory;
   QFileInfoList languageFileList;

public:
    LanguageControl();
    bool initialize();
    QStringList getLanguageList();
    bool loadLanguage(QString language);
    QString getTranslation(int translateThis);
    QStringList getTranslationList();
};

#endif // LANGUAGECONTROL_H
