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
        controller_updateView_view,
        controller_seriesSet_view
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
