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
    KeyPressEater *keyPressEaterDeleteFileType;
    KeyPressEater *keyPressEaterEnterFileType;
    KeyPressEater *keyPressEaterEscapeSettings;
    void createResetConfirmationDialog();
    void resizeNameSchemeTab();
    void setFileTypeList(QStringList fileTypes);

private slots:
    void onGUILanguageChanged(QString language);
    void onSeriesParserChanged();
    void onSaveSeriesChanged(bool saveSeries);
    void onSavePathChanged(bool savePath);
    void onResetClicked();
    void onDarkThemeChanged(bool useDarkTheme);
    void onShowSeriesInformationChanged(bool showInfo);
    void onTabChanged(int index);
    void onAddNameScheme();
    void onRemoveNameScheme();
    void onNameSchemeChanged(QListWidgetItem *item);
    void onNameSchemeSelectionChanged(int index);
    void onNameSchemeLineEditChanged();
    void onAddFileType();
    void onRemoveFileType();
    void onFileTypeChanged(QListWidgetItem *item);
    void onFileTypeSelectionChanged(int index);
    void onFileTypeLineEditChanged();

signals:
    void sendMessage(Message &msg);
};


#endif // SETTINGSWINDOW_H
