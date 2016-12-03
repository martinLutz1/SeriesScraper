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
        // View
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
        about,
        settings,
        fullscreen,
        language,
        display,
        help,
        // About dialg
        close,
        // Settings window
        done,
        yes,
        no,
        areYouSure,
        areYouSureDetailed,
        general,
        interface,
        darkTheme,
        showSeriesInformation,
        saveOnExit,
        seriesDatabase,
        recommended,
        newFormat,
        add,
        remove,
        video,
        newNameScheme,
        reset,
        resetAll,
        // Feedback
        notFound,
        seriesLanguageNotFound,
        nameSchemeFileNotFound,
        nameSchemeLineNotFound,
        renameFailed,
        renameSuccess,
    };

private:
    QStringList translations;
    QString selectedLanguage;
};

#endif // LANGUAGEDATA_H
