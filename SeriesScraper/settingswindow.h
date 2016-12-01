#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include "message.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();

public slots:
    void notify(Message &msg);

private:
    Ui::SettingsWindow *ui;
    void changeLocalization(QStringList translationList);

private slots:
    void onGUILanguageChanged(QString language);
    void onSeriesParserChanged();
    void onSaveSeriesChanged(bool saveSeries);
    void onSavePathChanged(bool savePath);

signals:
    void sendMessage(Message &msg);
};


#endif // SETTINGSWINDOW_H
