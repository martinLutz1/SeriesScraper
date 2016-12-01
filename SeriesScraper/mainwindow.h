#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define APPLICATIONNAME "SeriesScraper"

#include <QMainWindow>
#include <QDir>
#include <QLabel>
#include <QProgressBar>
#include <QGraphicsBlurEffect>
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
    QTimer *setPathTimer;
    QTimer *seriesTextChangeTimer;
    QTimer *progressBarTimer;
    QTimer *disableSeriesProgressbarTimer;
    QLabel *seriesStatusLabel;
    QProgressBar *seriesProgressBar;
    QGraphicsBlurEffect *blur;

    QMenu *helpMenu;
    QMenu *viewMenu;
    QAction *aboutAction;
    QAction *settingsAction;

    QDir chosenPath;
    int tableRows;
    int progressIncrement;
    QString whiteBackground;
    QString imageBackground;
    QStringList nameSchemeItemList;
    QString colorWhite = "QLineEdit { background: rgb(255, 255, 255); }";
    QString colorGreen = "QLineEdit { background: rgb(204, 255, 204); }";
    QString colorRed = "QLineEdit { background: rgb(255, 217, 204); }";
    QChar checkmark = QChar(0x13, 0x27);
    QChar times = QChar(0x15, 0x27);

    void setUpTable();
    void setUpMenuBar();
    void setSeriesAvailableStatus(bool status, bool isEmpty);
    void setAmountSeasons(int amount);
    void addNameSchemeItem(QString nameScheme);
    void removeNameSchemeItem(int itemIndex);
    void changeLocalization(QStringList translationList);
    void resizeEvent(QResizeEvent *event);
    void updateView(QStringList oldFileNames, QStringList newFileNames, int amountSeasons);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool setRow(int row, QString oldFileName, QString newFileName);
    void clearTable();

private slots:
    void openDirectory();
    void setPath();
    void startSetPathTimer();
    void startSeriesTextChangeTimer();
    void disableSeriesProgressbar();
    void updateProgressbar();
    void onCellChanged(int row, int coloumn);
    void onSeriesTextChanged();
    void onSeasonChanged(int index);
    void onSeriesLanguageChanged(int index);
    void onRenameButtonPressed();
    void onNameSchemeChanged(int index);
    void showAboutDialog();
    void showSettingsWindow();

public slots:
    void notify(Message &msg);

signals:
    void sendMessage(Message &msg);
};

#endif // MAINWINDOW_H
