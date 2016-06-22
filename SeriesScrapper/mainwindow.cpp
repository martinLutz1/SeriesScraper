#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "application.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent, Application* application) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    app(application),
    chosenPath(QDir::current()),
    tableRows(0)
{
    ui->setupUi(this);
    checkPathTimer = new QTimer(this);
    setUpTable();
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openDirectory()));
    QObject::connect(ui->pathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(startCheckPathTimer()));
    QObject::connect(checkPathTimer, SIGNAL(timeout()), this, SLOT(checkPath()));
    QObject::connect(ui->episodeNameTable, SIGNAL(cellChanged(int,int)), this, SLOT(onCellChange(int,int)));
    QObject::connect(ui->seriesLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onSeriesTextChange(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpTable()
{
    // Set table start size
    ui->episodeNameTable->setColumnCount(2);

    // Set Column width and name headers
    ui->episodeNameTable->setHorizontalHeaderLabels(QString("Episoden-Name;Datei-Name").split(";"));
    ui->episodeNameTable->setColumnWidth(0,300);
    ui->episodeNameTable->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::clearTable()
{
    for(int i = tableRows; i>=0; i--)
        ui->episodeNameTable->removeRow(i);
    tableRows = 0;
}

void MainWindow::openDirectory()
{
    // Open directory-dialog to chose directory
    QString directoryPath;
    directoryPath = QFileDialog::getExistingDirectory(this,"Ordner wählen", chosenPath.path());
    if (!directoryPath.isNull())
    {
        chosenPath = directoryPath; // Remember path
        ui->pathLineEdit->setText(directoryPath);
    }
}

void MainWindow::checkPath()
{
    checkPathTimer->stop();
    QDir dir;
    dir.setPath(ui->pathLineEdit->text());
    QString colorWhite = "QLineEdit { background: rgb(255, 255, 255); }";
    QString colorGreen = "QLineEdit { background: rgb(204, 255, 204); }";
    QString colorRed = "QLineEdit { background: rgb(255, 217, 204); }";
    QChar checkmark = QChar(0x13, 0x27);
    QChar times = QChar(0x15, 0x27);

    if (dir.path().isEmpty()) {
        ui->pathLineEdit->setStyleSheet(colorWhite);
        ui->correctPathLabel->setText("");
    }
    else if (dir.exists()) {
        ui->pathLineEdit->setStyleSheet(colorGreen);
        ui->correctPathLabel->setText(checkmark);
    }
    else {
        ui->pathLineEdit->setStyleSheet(colorRed);
        ui->correctPathLabel->setText(times);
    }
}

void MainWindow::startCheckPathTimer()
{
    checkPathTimer->start(500);
}

void MainWindow::onCellChange(int row, int coloumn)
{
    if (coloumn == 0) // Only Episode names
        app->setEpisode(row, ui->episodeNameTable->item(row, coloumn)->text());
}

void MainWindow::onSeriesTextChange(QString series)
{
qDebug() << series;
}

bool MainWindow::setRow(int row, QString episodeName, QString fileName)
{
    // Check if trying to access rows, that are not existent and not the next possible new row
    if (row > tableRows)
        return false;

    // Check if row items already exist to prevent multiple creations
    if (ui->episodeNameTable->item(row, 0) != NULL && ui->episodeNameTable->item(row, 1) != NULL) {
        ui->episodeNameTable->item(row, 0)->setText(episodeName);
        ui->episodeNameTable->item(row, 1)->setText(fileName);
    }
    else { // Not existing
        tableRows++;
        QTableWidgetItem *episode = new QTableWidgetItem(episodeName);
        QTableWidgetItem *file = new QTableWidgetItem(fileName);
        file->setFlags(file->flags() & ~Qt::ItemIsEditable);

        ui->episodeNameTable->setRowCount(tableRows);
        ui->episodeNameTable->setItem(row, 0, episode);
        ui->episodeNameTable->setItem(row, 1, file);
    }
    return true;
}

Ui::MainWindow *MainWindow::getUI()
{
    return ui;
}
