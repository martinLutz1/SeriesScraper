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
    seriesTextChangeTimer = new QTimer(this);
    setUpTable();
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openDirectory()));
    QObject::connect(ui->pathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(startCheckPathTimer()));
    QObject::connect(checkPathTimer, SIGNAL(timeout()), this, SLOT(checkPath()));
    QObject::connect(ui->episodeNameTable, SIGNAL(cellChanged(int,int)), this, SLOT(onCellChange(int,int)));
    QObject::connect(ui->seriesLineEdit, SIGNAL(textChanged(QString)), this, SLOT(startSeriesTextChangeTimer()));
    QObject::connect(seriesTextChangeTimer, SIGNAL(timeout()), this, SLOT(onSeriesTextChange()));
    QObject::connect(ui->seasonComboBox, SIGNAL(activated(int)), this , SLOT(onSeasonChanged(int)));
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

void MainWindow::setAmountSeasons(int amount)
{
    int recentAmount = ui->seasonComboBox->count();

    if (amount > recentAmount) { // More items requested than avaible, add
        for (; recentAmount < amount; recentAmount++)
            ui->seasonComboBox->addItem(QString::number(recentAmount + 1));
    }
    else if (amount < recentAmount) { // Delete some items to fit amount
        for (; recentAmount >= amount; recentAmount--)
            ui->seasonComboBox->removeItem(recentAmount);
    }
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

void MainWindow::startSeriesTextChangeTimer()
{
    seriesTextChangeTimer->start(500);
}

void MainWindow::onSeriesTextChange()
{
    seriesTextChangeTimer->stop();
    QString seriesText = ui->seriesLineEdit->text();

    if (seriesText.isEmpty()) {
        ui->seriesLineEdit->setStyleSheet(colorWhite);
        ui->correctSeriesLabel->setText("");
        setAmountSeasons(0);
        clearTable();
    }
    else if (app->setSeries(seriesText, 1)) {
        ui->seriesLineEdit->setStyleSheet(colorGreen);
        ui->correctSeriesLabel->setText(checkmark);
        ui->seasonComboBox->setCurrentIndex(0);
    }
    else {
        ui->seriesLineEdit->setStyleSheet(colorRed);
        ui->correctSeriesLabel->setText(times);
        clearTable();
        setAmountSeasons(0);
    }
}

void MainWindow::onSeasonChanged(int index)
{
    app->setSeries(app->getSeries(), index + 1);
    ui->seasonComboBox->setCurrentIndex(index);
}

void MainWindow::onCellChange(int row, int coloumn)
{
    if (coloumn == 0) // Only Episode names
        app->setEpisode(row, ui->episodeNameTable->item(row, coloumn)->text());
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
