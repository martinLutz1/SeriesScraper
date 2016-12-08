#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include "message.h"
#include "keypresseater.h"

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
    KeyPressEater *keyPressEaterDeleteNameScheme;
    KeyPressEater *keyPressEaterEnterNameScheme;
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
    void onNameSchemeChanged(QListWidgetItem *item);
    void onNameSchemeSelectionChanged(int index);
    void onRemoveNameScheme();
    void onAddNameScheme();
    void onNameSchemeLineEditChanged();

signals:
    void sendMessage(Message &msg);
};


#endif // SETTINGSWINDOW_H
