#include "languagedata.h"
#include <QDebug>

LanguageData::LanguageData()
{
}

QString LanguageData::getLanguage()
{
    return selectedLanguage;
}

QString LanguageData::getTranslation(Translate toTranslate)
{
    return translations.at((int)toTranslate);
}

QStringList LanguageData::getTranslationList()
{
    return translations;
}

void LanguageData::setLanguage(QString language)
{
    selectedLanguage = language;
}

void LanguageData::setTranslation(Translate toTranslate, QString translation)
{
    // Prepare space
    while (translations.size() <= (int)toTranslate)
    {
        translations.push_back(QString());
    }

    translations[(int)toTranslate] = translation;
}

void LanguageData::setTranslationSet(QStringList translationList)
{
    translations = translationList;
}

