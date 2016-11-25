#include "languagedata.h"

LanguageData::LanguageData()
{
}

QString LanguageData::getLanguage()
{
    return selectedLanguage;
}

QString LanguageData::getTranslation(int toTranslate)
{
    return translations.at(toTranslate);
}

QStringList LanguageData::getTranslationList()
{
    return translations;
}

void LanguageData::setLanguage(QString language)
{
    selectedLanguage = language;
}

void LanguageData::setTranslation(int toTranslate, QString translation)
{
    // Prepare space
    while (translations.size() <= toTranslate)
        translations.push_back(QString(""));

    translations[toTranslate] = translation;
}

void LanguageData::setTranslationSet(QStringList translationList)
{
    translations = translationList;
}

