#ifndef LANGUAGECONTROL_H
#define LANGUAGECONTROL_H

#include "languagedata.h"
#include <QDir>


class LanguageControl
{
private:
   LanguageData languageData;
   QDir languageFileDirectory;

public:
    LanguageControl();
    bool initialize();
    bool loadLanguage(QString language);
    QString getTranslation(int translateThis);
    QStringList getTranslationList();
};

#endif // LANGUAGECONTROL_H
