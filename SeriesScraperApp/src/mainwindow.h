#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define APPLICATIONNAME "SeriesScraper"


#include <QMainWindow>
#include <QDir>
#include <QLabel>
#include <QStyleFactory>
#include <QMessageBox>
#include <QComboBox>
#include <QPropertyAnimation>

#include "customshadoweffect.h"
#include "QProgressIndicator.h"
#include "lineedit.h"
#include "keypresseater.h"
#include "aboutdialog.h"
#include "message.h"
#include "episodename.h"
#include "settings.h" // DirectorySelector enum.
#include "directoryparser.h" // NUMBER_PATH_STRUCTURE_COMBOBOXES

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    enum class StatusMessageType { error, success, info };

private:
    Ui::MainWindow *ui;
    QTimer *seriesTextChangeTimer;
    QTimer *clearStatusTextTimer;
    QTimer *hideRenameProgressTimer;
    QLabel *statusBarTypeImageLabel;
    CustomShadowEffect *renameShadow;
    QPropertyAnimation *renameSlideProgressAnimation;
    QProgressIndicator *progressIndicatorPath;
    QProgressIndicator *progressIndicatorSeries;
    KeyPressEater *keyPressEaterEscape;
    KeyPressEater *keyPressEaterEnter;
    QMessageBox *renameConfirmationMessageBox;
    QMessageBox *posterConfirmationMessageBox;
    QMessageBox *undoRenameConfirmationBox;
    QComboBox* pathStructureComboBoxList[NUMBER_PATH_STRUCTURE_COMBOBOXES];

    QMenu *fileMenu;
    QMenu *directoryMenu;
    QMenu *helpMenu;
    QMenu *viewMenu;
    QMenu *appearanceMenu;
    QMenu *directoryEntriesMenu;
    QAction *savePosterAction;
    QAction *undoRenameAction;
    QAction *openDirectoryAction;
    QAction *switchDirectorySelectorAction;
    QAction *reloadDirectoryAction;
    QAction *aboutAction;
    QAction *settingsAction;
    QAction *fullScreenAction;

    QDir chosenPath;
    QString whiteBackground;
    QString imageBackground;
    QStringList nameSchemeItemList;
    QString colorWhite = "QLineEdit { background: rgb(255, 255, 255); }";
    QString colorGreen = "QLineEdit { background: rgb(204, 255, 204); }";
    QString colorRed = "QLineEdit { background: rgb(255, 217, 204); }";
    QColor greyedOutColor {100, 100, 100};
    QColor normalColor {0, 0, 0};
    QColor lightRedColor {255, 142, 142};
    QColor whiteColor {255, 255, 255};
    QPixmap seriesImage;
    bool fullScreenEnabled = false;
    bool seriesInformationEnabled = false;
    QString directorySelectionText = "Directory selection";
    QString openThisFolderText = "Open this folder";
    bool isRenameProgressHiding = false;
    Settings::DirectorySelector directorySelector = Settings::DirectorySelector::widget;

    void disableGUIControl();
    void enableGUIControl();
    void setUpGUI();
    void setUpTable();
    void setUpMenuBar();
    void setUpConfirmationMessageBoxes();
    void setUpDirectoryWidget();
    void setUpRenameProgressWidget();
    void setSeriesAvailableStatus(bool status, bool isEmpty);
    void setPathCorrectStatus(bool status, bool isEmpty);
    void setAmountSeasons(int amount);
    void addNameSchemeItem(QString nameScheme);
    void removeNameSchemeItem(int itemIndex);
    void setStatusMessage(QString message, StatusMessageType type);
    void changeLocalization(QStringList translationList);
    void resizeEvent(QResizeEvent *event);
    void updateView(EpisodeNames* episodeNames, bool atLeastOneSideEmpty, int amountSeasons);
    void updateDirectoryWidget(std::vector<QStringList> pathStructure, bool containsRoot, QString path);
    void clearDirectoryWidget();
    void updateDirectoryWidgetVisibility();
    void changeToDarkTheme();
    void showSeriesLoadingAnimation();
    void hideSeriesLoadingAnimation();
    void showRenameProgress();
    void hideRenameProgress();
    void updateRenameProgress(int amountFiles, int currentFile, QString oldFileName);
    void switchDirectorySelector(Settings::DirectorySelector directorySelector);

private slots:
    void updateRow(int row, EpisodeName& episodeName, bool noColorization);
    void clearTable();
    void openDirectory();
    void onUpdateDirectory();
    void startSeriesTextChangeTimer();
    void onSeriesTextChanged();
    void onSeasonChanged(int index);
    void onSeriesLanguageChanged(int index);
    void onRenameButtonPressed();
    void onNameSchemeChanged(int index);
    void onTableEntryChanged(int row, int coloumn);
    void onPathLineEditTextChanged(QString path);
    void onDirectoryEntryClicked(QAction* clickedAction);
    void onDirectoryComboBox1EntryClicked(int selection);
    void onDirectoryComboBox2EntryClicked(int selection);
    void onDirectoryComboBox3EntryClicked(int selection);
    void onDirectoryComboBox4EntryClicked(int selection);
    void onDirectoryComboBoxEntryClicked(int level, int selection);
    void toggleDirectorySelector();
    void clearStatusText();

    void savePoster();
    void undoRenaming();
    void showAboutDialog();
    void showSettingsWindow();
    void toggleFullScreen();
    void onPathStructureContentButtonClicked();
    void slideOutRenameProgressWidget();
    void hideRenameProgressWidget();

public slots:
    void notify(Message &msg);

signals:
    void sendMessage(Message &msg);
};

#endif // MAINWINDOW_H
