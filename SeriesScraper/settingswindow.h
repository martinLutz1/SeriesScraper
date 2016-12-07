#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QMessageBox>
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
    QMessageBox resetConfirmationMessageBox;
    QSize windowSize;
    void createResetConfirmationDialog();
    void resizeNameSchemeTab();

private slots:
    void onGUILanguageChanged(QString language);
    void onSeriesParserChanged();
    void onSaveSeriesChanged(bool saveSeries);
    void onSavePathChanged(bool savePath);
    void onResetClicked();
    void onDarkThemeChanged(bool useDarkTheme);
    void onTabChanged(int index);

signals:
    void sendMessage(Message &msg);
};


#endif // SETTINGSWINDOW_H
