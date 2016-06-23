#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>

class Application;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0, Application* application = NULL);
    ~MainWindow();
    bool setRow(int row, QString episodeName, QString fileName);
    void clearTable();
    void setAmountSeasons(int amount);

private slots:
    void openDirectory();
    void checkPath();
    void startCheckPathTimer();
    void startSeriesTextChangeTimer();
    void onCellChange(int row, int coloumn);
    void onSeriesTextChange();
    void onSeasonChanged(int index);

private:
    Ui::MainWindow *ui;
    Application *app;
    QDir chosenPath;
    int tableRows;
    QTimer *checkPathTimer;
    QTimer *seriesTextChangeTimer;
    QPalette whiteBackground;
    QPalette backgroundImage;

    QString colorWhite = "QLineEdit { background: rgb(255, 255, 255); }";
    QString colorGreen = "QLineEdit { background: rgb(204, 255, 204); }";
    QString colorRed = "QLineEdit { background: rgb(255, 217, 204); }";
    QChar checkmark = QChar(0x13, 0x27);
    QChar times = QChar(0x15, 0x27);

    void setUpTable();
};

#endif // MAINWINDOW_H
