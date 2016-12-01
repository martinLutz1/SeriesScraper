#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QStringList>

class Message
{
public:
    enum MessageType
    {
        view_changeSeriesText_controller,
        view_changeSeason_controller,
        view_changeEpisodeName_controller,
        view_changeDirectory_controller,
        view_rename_controller,
        view_changeNameScheme_controller,
        view_changeSeriesLanguage_controller,
        view_showAboutDialog_controller,
        view_showSettingsWindow_controller,

        settings_changeGUILanguage_controller,
        settings_changeSeriesParser_controller,
        settings_saveSeries_controller,
        settings_savePath_controller,
        settings_reset_controller,

        controller_updateView_view,
        controller_seriesSet_view,
        controller_setSeries_view,
        controller_setPath_view,
        controller_enableButton_view,
        controller_startSeriesLoading_view,
        controller_successSeriesLoading_view,
        controller_failureSeriesLoading_view,
        controller_addNameSchemes_view,
        controller_addSeriesLanguages_view,
        controller_changeLocalization_view,
        controller_setStatus_view,
        controller_changeSeriesParser_view,
        controller_changeSeriesLanguage_view,
        controller_showAboutDialog_about,
        controller_showSettingsWindow_settings,
        controller_addGUILanguages_settings,
        controller_noGUILanguagesFound_settings,
        controller_saveSeries_settings,
        controller_savePath_settings
    };

    union MessageData {
        QString* qsPointer;
        QStringList* qsListPointer;
        int i;
        bool b;
    };

    MessageType type;
    MessageData data[6];

    Message();
};

#endif // MESSAGE_H
