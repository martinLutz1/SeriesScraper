#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QStringList>
#include <QRect>
#include <vector>
#include "episodename.h"

class Message
{
public:
    enum class Type
    {
        view_changeSeriesText_controller,
        view_changeSeason_controller,
        view_changeNewFileName_controller,
        view_getEpisodeName_controller,
        view_changeDirectory_controller,
        view_updateDirectory_controller,
        view_switchToDirectory_controller,
        view_rename_controller,
        view_forceRename_controller,
        view_undoRenaming_controller,
        view_changeNameScheme_controller,
        view_changeSeriesLanguage_controller,
        view_savePoster_controller,
        view_forceSavePoster_conroller,
        view_showAboutDialog_controller,
        view_showSettingsWindow_controller,
        view_setWindowRect_controller,

        settings_changeGUILanguage_controller,
        settings_changeSeriesParser_controller,
        settings_saveSeries_controller,
        settings_savePath_controller,
        settings_savePoster_controller,
        settings_setDetectedSeason_controller,
        settings_reset_controller,
        settings_useDarkTheme_controller,
        settings_showSeriesInfo_controller,
        settings_addFileType_controller,
        settings_removeFileType_controller,
        settings_replaceFileType_controller,
        settings_addNameScheme_controller,
        settings_removeNameScheme_controller,
        settings_replaceNameScheme_controller,

        controller_updateView_view,
        controller_seriesSet_view,
        controller_setSeries_view,
        controller_setSeason_view,
        controller_startDirectoryLoading_view,
        controller_stopDirectoryLoading_view,
        controller_setPath_view,
        controller_DirectorySetSuccessful_view,
        controller_setWindowRect_view,
        controller_updateDirectoryWidget_view,
        controller_enableRenameButton_view,
        controller_enableSavePoster_view,
        controller_startSeriesLoading_view,
        controller_successSeriesLoading_view,
        controller_failureSeriesLoading_view,
        controller_renameStarted_view,
        controller_updateRenameProgess_view,
        controller_renameFinished_view,
        controller_enableUndoRenaming_view,
        controller_addNameScheme_view,
        controller_addNameSchemes_view,
        controller_addSeriesLanguages_view,
        controller_changeLocalization_view,
        controller_setStatus_view,
        controller_changeSeriesParser_view,
        controller_changeSeriesLanguage_view,
        controller_changeNameScheme_view,
        controller_replaceNameScheme_view,
        controller_returnEpisodeName_view,
        controller_seasonMismatch_view,
        controller_useDarkTheme_view,
        controller_showSeriesInfo_view,
        controller_setSeriesInfo_view,
        controller_removeNameScheme_view,
        controller_posterAlreadyExists_view,

        controller_showAboutDialog_about,
        controller_showSettingsWindow_settings,
        controller_addGUILanguages_settings,
        controller_noGUILanguagesFound_settings,
        controller_saveSeries_settings,
        controller_savePath_settings,
        controller_savePoster_settings,
        controller_setDetectedSeason_settings,
        controller_useDarkTheme_settings,
        controller_showSeriesInfo_settings,
        controller_addRawNameScheme_settings,
        controller_setRawNameSchemes_settings,
        controller_setFileTypes_settings,
        controller_addFileType_settings,
        controller_removeFileType_settings,
        controller_replaceFileType_settings
    };

    union Data {
        QString* qsPointer;
        QStringList* qsListPointer;
        std::vector<QStringList> *qsListVectorPointer;
        QRect *qRectPointer;
        QByteArray* qbPointer;
        EpisodeNames* episodeNamesPointer;
        int i;
        bool b;
    };

    Type type;
    Data data[7];

    Message();
};

#endif // MESSAGE_H
