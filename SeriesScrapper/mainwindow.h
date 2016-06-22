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
    Ui::MainWindow *getUI();

private slots:
    void openDirectory();
    void checkPath();
    void startCheckPathTimer();
    void onCellChange(int row, int coloumn);
    void onSeriesTextChange(QString series);

private:
    Ui::MainWindow *ui;
    Application *app;
    QDir chosenPath;
    int tableRows;
    QTimer *checkPathTimer;

    void setUpTable();
    void clearTable();
};

#endif // MAINWINDOW_H
