#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define APPLICATIONNAME "SeriesScraper"
#define NUMBER_PATH_STRUCTURE_COMBOBOXES 4

#include <QMainWindow>
#include <QDir>
#include <QLabel>
#include <QGraphicsBlurEffect>
#include <QStyleFactory>
#include <QMessageBox>
#include <QComboBox>
#include "customshadoweffect.h"
#include "QProgressIndicator.h"
#include "keypresseater.h"
#include "aboutdialog.h"
#include "message.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QTimer *seriesTextChangeTimer;
    QTimer *clearStatusTextTimer;
    QLabel *statusBarTypeImageLabel;
    QGraphicsBlurEffect *blur;
    CustomShadowEffect *shadow;
    QProgressIndicator *progressIndicatorPath;
    QProgressIndicator *progressIndicatorSeries;
    KeyPressEater *keyPressEaterEscape;
    KeyPressEater *keyPressEaterEnter;
    QMessageBox *renameConfirmationMessageBox;
    QMessageBox *posterConfirmationMessageBox;
    QMessageBox *undoRenameConfirmationBox;
    QComboBox* pathStructureComboBoxList[NUMBER_PATH_STRUCTURE_COMBOBOXES];

    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *viewMenu;
    QMenu *appearanceMenu;
    QMenu *directoryEntriesMenu;
    QAction *savePosterAction;
    QAction *undoRenameAction;
    QAction *aboutAction;
    QAction *settingsAction;
    QAction *fullScreenAction;

    QDir chosenPath;
    int progressIncrement;
    QString whiteBackground;
    QString imageBackground;
    QStringList nameSchemeItemList;
    QString colorWhite = "QLineEdit { background: rgb(255, 255, 255); }";
    QString colorGreen = "QLineEdit { background: rgb(204, 255, 204); }";
    QString colorRed = "QLineEdit { background: rgb(255, 217, 204); }";
    QPixmap seriesImage;
    bool fullScreenEnabled = false;
    bool seriesInformationEnabled = false;
    QString directorySelectionText = "Directory selection";
    QString openThisFolderText = "Open this folder";

    void disableGUIControl();
    void enableGUIControl();
    void setUpGUI();
    void setUpTable();
    void setUpMenuBar();
    void setUpConfirmationMessageBoxes();
    void setUpDirectoryWidget();
    void setSeriesAvailableStatus(bool status, bool isEmpty);
    void setAmountSeasons(int amount);
    void addNameSchemeItem(QString nameScheme);
    void removeNameSchemeItem(int itemIndex);
    void setStatusMessage(QString message, int type);
    void changeLocalization(QStringList translationList);
    void resizeEvent(QResizeEvent *event);
    void updateView(QStringList oldFileNames, QStringList newFileNames, int amountSeasons);
    void updateDirectoryWidget(std::vector<QStringList> pathStructure, bool containsRoot, QString path);
    void clearDirectoryWidget();
    void updateDirectoryWidgetVisibility();
    void changeToDarkTheme();
    void showSeriesLoadingAnimation();
    void hideSeriesLoadingAnimation();

public:
    explicit MainWindow(QWidget *parent = 0);
    enum statusMessageType
    {
        error,
        success,
        info
    };

    ~MainWindow();

private slots:
    bool updateRow(int row, QString oldFileName, QString newFileName, bool noColorization);
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
    void onDirectoryEntryClicked(QAction* clickedAction);
    void onDirectoryComboBox1EntryClicked(int selection);
    void onDirectoryComboBox2EntryClicked(int selection);
    void onDirectoryComboBox3EntryClicked(int selection);
    void onDirectoryComboBox4EntryClicked(int selection);
    void onDirectoryComboBoxEntryClicked(int level, int selection);
    void clearStatusText();

    void savePoster();
    void undoRenaming();
    void showAboutDialog();
    void showSettingsWindow();
    void toggleFullScreen();
    void onPathStructureContentButtonClicked();

public slots:
    void notify(Message &msg);

signals:
    void sendMessage(Message &msg);
};

#endif // MAINWINDOW_H
