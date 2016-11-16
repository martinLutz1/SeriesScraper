#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QStringList>

class Message
{
public:
    enum MessageType
    {
        view_seriesText_changed_controller,
        view_season_changed_controller,
        view_episodeName_changed_controller,
        view_directory_changed_controller,
        view_rename_controller,
        view_changeNameScheme_controller,
        view_changeGUILanguage_controller,
        view_changeSeriesLanguage_controller,
        view_showAboutDialog_controller,
        view_showSettingsWindow_controller,

        controller_updateView_view,
        controller_seriesSet_view,
        controller_enableButton_view,
        controller_startSeriesLoading_view,
        controller_successSeriesLoading_view,
        controller_failureSeriesLoading_view,
        controller_addNameScheme_view,
        controller_changeLocalization_view,
        controller_addSeriesLanguage_view,
        controller_showAboutDialog_about,
        controller_showSettingsWindow_settings
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
