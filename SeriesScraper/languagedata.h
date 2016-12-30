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
        about,
        add,
        airDate,
        areYouSure,
        areYouSureDetailed,
        close,
        darkTheme,
        directorySelection,
        display,
        done,
        episodeNumber,
        file,
        forceRename,
        fullscreen,
        general,
        help,
        interface,
        language,
        nameScheme,
        nameSchemeFileNotFound,
        nameSchemeLineNotFound,
        newFormat,
        newName,
        newNameScheme,
        no,
        notFound,
        oldName,
        overridePoster,
        path,
        poster,
        posterAlreadyExists,
        posterNotSaved,
        posterSaved,
        recommended,
        remove,
        rename,
        renameFailed,
        renameSuccess,
        reset,
        resetAll,
        saveInSeriesDirectory,
        saveOnExit,
        savePoster,
        season,
        selection,
        series,
        seriesDatabase,
        seriesInfo,
        seriesLanguageNotFound,
        seriesSelection,
        settings,
        showSeriesInformation,
        video,
        yes,
    };

private:
    QStringList translations;
    QString selectedLanguage;
};

#endif // LANGUAGEDATA_H
