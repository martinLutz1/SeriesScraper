#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    chosenPath(QDir::current()),
    tableRows(0),
    backgroundImage(whiteBackground)
{
    ui->setupUi(this);
    setPathTimer = new QTimer(this);
    seriesTextChangeTimer = new QTimer(this);

    // Table
    setUpTable();
    whiteBackground = ui->episodeNameTable->palette();
    backgroundImage = whiteBackground;
    QPixmap px(":/images/table_bg.png");
    backgroundImage.setBrush(QPalette::Base, QBrush(px));
    ui->episodeNameTable->setPalette(backgroundImage);

    // Remove, when implemented!
    ui->nameSchemeComboBox->addItem("1: series - s*e* - ep.*");

    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openDirectory()));
    QObject::connect(ui->pathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(startSetPathTimer()));
    QObject::connect(setPathTimer, SIGNAL(timeout()), this, SLOT(setPath()));
    QObject::connect(ui->episodeNameTable, SIGNAL(cellChanged(int,int)), this, SLOT(onCellChange(int,int)));
    QObject::connect(ui->seriesLineEdit, SIGNAL(textChanged(QString)), this, SLOT(startSeriesTextChangeTimer()));
    QObject::connect(seriesTextChangeTimer, SIGNAL(timeout()), this, SLOT(onSeriesTextChange()));
    QObject::connect(ui->seasonComboBox, SIGNAL(activated(int)), this, SLOT(onSeasonChanged(int)));
    QObject::connect(ui->renameButton, SIGNAL(pressed()), this , SLOT(onRenameButtonPressed()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpTable()
{
    // Set table start size
    ui->episodeNameTable->setColumnCount(3);

    // Set Column width and name headers
    ui->episodeNameTable->setHorizontalHeaderLabels(QString("Episoden-Name;Datei-Name(neu);Datei-Name(alt)").split(";"));
    ui->episodeNameTable->setColumnWidth(0,250);
    ui->episodeNameTable->setColumnWidth(1,400);
    ui->episodeNameTable->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::setSeriesAvailableStatus(bool status, bool isEmpty)
{
    if (status) {
        ui->seriesLineEdit->setStyleSheet(colorGreen);
        ui->correctSeriesLabel->setText(checkmark);
        ui->seasonComboBox->setCurrentIndex(0);
    }
    else if (isEmpty) {
        ui->seriesLineEdit->setStyleSheet(colorWhite);
        ui->correctSeriesLabel->setText("");
        setAmountSeasons(0);
        clearTable();
    }
    else {
        ui->seriesLineEdit->setStyleSheet(colorRed);
        ui->correctSeriesLabel->setText(times);
        clearTable();
        setAmountSeasons(0);
    }
}

void MainWindow::clearTable()
{
    ui->episodeNameTable->setPalette(backgroundImage);
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

void MainWindow::setPath()
{
    setPathTimer->stop();
    QDir dir;
    dir.setPath(ui->pathLineEdit->text());

    if (dir.path().isEmpty()) {
        ui->pathLineEdit->setStyleSheet(colorWhite);
        ui->correctPathLabel->setText("");
    }
    else if (dir.exists()) {
        ui->pathLineEdit->setStyleSheet(colorGreen);
        ui->correctPathLabel->setText(checkmark);

        QString directory = dir.path();
        Message directoryChangedMsg;
        directoryChangedMsg.type = Message::view_directory_changed_controller;
        directoryChangedMsg.data[0].qsPointer = &directory;
        emit(sendMessage(directoryChangedMsg));
    }
    else {
        ui->pathLineEdit->setStyleSheet(colorRed);
        ui->correctPathLabel->setText(times);
    }
}

void MainWindow::startSetPathTimer()
{
    setPathTimer->start(500);
}

void MainWindow::startSeriesTextChangeTimer()
{
    seriesTextChangeTimer->start(1000);
}

void MainWindow::onSeriesTextChange()
{
    seriesTextChangeTimer->stop();
    QString seriesText = ui->seriesLineEdit->text();

    Message msg;
    msg.type = Message::view_seriesText_changed_controller;
    msg.data[0].qsPointer = &seriesText;
    msg.data[1].i = 1;
    emit sendMessage(msg);
}

void MainWindow::onSeasonChanged(int index)
{
    Message seasonChangedMsg;
    seasonChangedMsg.type = Message::view_season_changed_controller;
    seasonChangedMsg.data[0].i = index + 1;
    emit(sendMessage(seasonChangedMsg));

    ui->seasonComboBox->setCurrentIndex(index);
}

void MainWindow::onRenameButtonPressed()
{
    Message renameMsg;
    renameMsg.type = Message::view_rename_controller;
    emit(sendMessage(renameMsg));
}

void MainWindow::onCellChange(int row, int coloumn)
{
    if (coloumn == 0) { // Only Episode names
        QString newEpisodeName = ui->episodeNameTable->item(row, coloumn)->text();
        //app->changeEpisodeName(row, newEpisodeName);
    }
}

void MainWindow::notify(Message &msg)
{
    switch (msg.type) {
    case Message::controller_updateView_view:
    {
        int amountSeasons = msg.data[0].i;
        QStringList episodeNameList = *msg.data[1].qsListPointer;
        QStringList newFileNameList = *msg.data[2].qsListPointer;
        QStringList oldFileNameList = *msg.data[3].qsListPointer;

        setAmountSeasons(amountSeasons);
        clearTable();
        for (int i = 0; i < episodeNameList.length(); i++)
            setRow(i, episodeNameList.at(i), newFileNameList.at(i), oldFileNameList.at(i));
        break;
    }

    case Message::controller_seriesSet_view:
    {
        bool seriesSet = msg.data[0].b;
        bool isEmpty = msg.data[1].b;
        setSeriesAvailableStatus(seriesSet, isEmpty);
        break;
    }

    default:
        break;
    }
}

bool MainWindow::setRow(int row, QString episodeName, QString newFileName, QString oldFileName)
{
    // Check if trying to access rows, that are not existent and not the next possible new row
    if (row > tableRows)
        return false;
    else
        ui->episodeNameTable->setPalette(whiteBackground);

    // Check if row items already exist to prevent multiple creations
    if (ui->episodeNameTable->item(row, 0) != NULL && ui->episodeNameTable->item(row, 1) != NULL) {
        ui->episodeNameTable->item(row, 0)->setText(episodeName);
        ui->episodeNameTable->item(row, 1)->setText(newFileName);
        ui->episodeNameTable->item(row, 2)->setText(oldFileName);
    }
    else { // Not existing
        tableRows++;
        QTableWidgetItem *episode = new QTableWidgetItem(episodeName);
        QTableWidgetItem *newFile = new QTableWidgetItem(newFileName);
        QTableWidgetItem *oldFile = new QTableWidgetItem(oldFileName);
        newFile->setFlags(newFile->flags() & ~Qt::ItemIsEditable);
        oldFile->setFlags(oldFile->flags() & ~Qt::ItemIsEditable);

        ui->episodeNameTable->setRowCount(tableRows);
        ui->episodeNameTable->setItem(row, 0, episode);
        ui->episodeNameTable->setItem(row, 1, newFile);
        ui->episodeNameTable->setItem(row, 2, oldFile);
    }
    return true;
}
