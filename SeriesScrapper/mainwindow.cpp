#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chosenPath = QDir::current();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDirectory()
{
    // Öffnet den Filedialog zum Laden eines Programms
    QString directoryPath;
    directoryPath = QFileDialog::getExistingDirectory(this,"Ordner wählen", chosenPath.path());
    qDebug() << directoryPath;
    if (!directoryPath.isNull())
    {
        chosenPath = directoryPath; // Speichere Pfad für nächstes Öffnen
    }
}
