#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QDir chosenPath;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openDirectory();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
