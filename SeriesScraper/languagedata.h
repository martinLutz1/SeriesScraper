#ifndef LANGUAGEDATA_H
#define LANGUAGEDATA_H
#include <QStringList>

class LanguageData
{
public:
    LanguageData();
    QString getLanguage();
    QString getTranslation(int toTranslate);
    QStringList getTranslationList();
    void setLanguage(QString language);
    void setTranslation(int toTranslate, QString translation);
    void setTranslationSet(QStringList translationList);

    enum translate {
        oldName,
        newName,
        directorySelection,
        selection,
        path,
        seriesSelection,
        series,
        season,
        nameScheme,
        rename,
        settings,
        language,
        // Errors
        notFound
    };

private:
    QStringList translations;
    QString selectedLanguage;
};

#endif // LANGUAGEDATA_H
