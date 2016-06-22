#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <jsonparser.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.openDirectory();
    JsonParser jsonP;
    /*for(int i = 1; i < 30; i++) {
        QString url = "http://www.omdbapi.com/?t=lost&type=series&season=1&episode=" + QString::number(i);
        qDebug() << jsonP.getIDfromURL(url, "Title");
    }*/

    return a.exec();
}

