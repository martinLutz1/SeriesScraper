#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QLabel>
#include <QProgressBar>
#include <QGraphicsBlurEffect>
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

    QDir chosenPath;
    int tableRows;
    int progressIncrement;
    QString whiteBackground;
    QString imageBackground;
    QString colorWhite = "QLineEdit { background: rgb(255, 255, 255); }";
    QString colorGreen = "QLineEdit { background: rgb(204, 255, 204); }";
    QString colorRed = "QLineEdit { background: rgb(255, 217, 204); }";
    QChar checkmark = QChar(0x13, 0x27);
    QChar times = QChar(0x15, 0x27);

    void setUpTable();
    void setSeriesAvailableStatus(bool status, bool isEmpty);
    void resizeEvent(QResizeEvent *event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool setRow(int row, QString episodeName, QString newFileName, QString oldFileName);
    void clearTable();
    void setAmountSeasons(int amount);

private slots:
    void openDirectory();
    void setPath();
    void startSetPathTimer();
    void startSeriesTextChangeTimer();
    void disableSeriesProgressbar();
    void updateProgressbar();
    void onCellChange(int row, int coloumn);
    void onSeriesTextChange();
    void onSeasonChanged(int index);
    void onRenameButtonPressed();

public slots:
    void notify(Message &msg);

signals:
    void sendMessage(Message &msg);
};

#endif // MAINWINDOW_H
