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
    const auto index = (int)toTranslate;
    // Prepare space
    translations.reserve((index));
    while (translations.size() <= index)
    {
        translations.push_back(QString());
    }

    translations[index] = translation;
}

void LanguageData::setTranslationSet(QStringList translationList)
{
    translations = translationList;
}

