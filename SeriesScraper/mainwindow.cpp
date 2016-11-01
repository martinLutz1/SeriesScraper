#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QTimer>
#include <QDebug>
#define UNIVERSAL_SPACER 10
#define GROUPBOX_HEIGHT 70

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    chosenPath(QDir::current()),
    tableRows(0)
{
    ui->setupUi(this);
    setPathTimer = new QTimer(this);
    seriesTextChangeTimer = new QTimer(this);

    // Table
    setUpTable();
    whiteBackground = QString("background-image: none; ") +
            QString("background-color: rgb(255, 255, 255);");
    imageBackground = QString("background-image: url(:/images/table_bg.png); ") +
            QString("background-color: rgb(255, 255, 255);") +
            QString("background-repeat: no-repeat; ") +
            QString("background-attachment: fixed; ") +
            QString("background-position: center;");

    ui->episodeNameTable->setStyleSheet(imageBackground);

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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    int windowHeight = this->centralWidget()->height();
    int windowWidth = this->centralWidget()->width();
    int pathBoxWidth = ui->pathGroupBox->width();
    int seriesBoxWidth = ui->seriesGroupBox->width();
    int nameSchemeBoxWidth = ui->nameSchemeGroupBox->width();
    int buttonWidth = ui->renameButton->width();
    int episodeTableWidth = windowWidth - 2 * UNIVERSAL_SPACER;


    if (windowWidth >= 1050) { // Representation for higher resolutions
        int spaceBetweenGroupboxes = (windowWidth - pathBoxWidth - seriesBoxWidth
                                      - nameSchemeBoxWidth - buttonWidth - 2 * UNIVERSAL_SPACER) / 3;

        // Resize table height
        int episodeTableHeight = windowHeight - GROUPBOX_HEIGHT - 2 * UNIVERSAL_SPACER;
        ui->episodeNameTable->setFixedSize(episodeTableWidth, episodeTableHeight);

        // Move path selector
        int pathBoxX = UNIVERSAL_SPACER;
        int pathBoxY = windowHeight - GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->pathGroupBox->move(pathBoxX, pathBoxY);

        // Move series selector
        int seriesBoxX = pathBoxWidth + UNIVERSAL_SPACER + spaceBetweenGroupboxes;
        int seriesBoxY = windowHeight - GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->seriesGroupBox->move(seriesBoxX, seriesBoxY);

        // Move name scheme selector
        int nameSchemeBoxX = pathBoxWidth + seriesBoxWidth + UNIVERSAL_SPACER + 2 * spaceBetweenGroupboxes;
        int nameSchemeBoxY = windowHeight - GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->nameSchemeGroupBox->move(nameSchemeBoxX, nameSchemeBoxY);
    }
    else if (windowWidth > 720){ // Representation for lower resolutions (720 < resolution < 1050)
        // Align the boxes relatively left and right
        int spaceBetweenGroupboxes = (windowWidth - pathBoxWidth - seriesBoxWidth - nameSchemeBoxWidth) / 3;
        if (spaceBetweenGroupboxes < UNIVERSAL_SPACER) // Make sure there is enough space bewteen the boxes
            spaceBetweenGroupboxes = UNIVERSAL_SPACER;

        // Resize table height
        int episodeTableHeight = windowHeight - 2 * GROUPBOX_HEIGHT - 3 * UNIVERSAL_SPACER;
        ui->episodeNameTable->setFixedSize(episodeTableWidth, episodeTableHeight);

        // Move path selector
        int pathBoxX = spaceBetweenGroupboxes;
        int pathBoxY = windowHeight - 2 * GROUPBOX_HEIGHT - 2 * UNIVERSAL_SPACER;
        ui->pathGroupBox->move(pathBoxX, pathBoxY);

        // Move series selector
        int seriesBoxX = pathBoxWidth + 2 * spaceBetweenGroupboxes;
        int seriesBoxY = windowHeight - 2 * GROUPBOX_HEIGHT - 2 * UNIVERSAL_SPACER;
        ui->seriesGroupBox->move(seriesBoxX, seriesBoxY);

        // Move name scheme selector
        int nameSchemeBoxX = windowWidth - buttonWidth - nameSchemeBoxWidth - 2 * UNIVERSAL_SPACER;
        int nameSchemeBoxY = windowHeight - GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->nameSchemeGroupBox->move(nameSchemeBoxX, nameSchemeBoxY);
    }
    else { // Representation for lowest resolutions (540 >= resolution >= 720)
        // Resize table height
        int episodeTableHeight = windowHeight - 2 * GROUPBOX_HEIGHT - 3 * UNIVERSAL_SPACER;
        ui->episodeNameTable->setFixedSize(episodeTableWidth, episodeTableHeight);

        // Move path selector
        int pathBoxX = UNIVERSAL_SPACER;
        int pathBoxY = windowHeight - 2 * GROUPBOX_HEIGHT - 2 * UNIVERSAL_SPACER;
        ui->pathGroupBox->move(pathBoxX, pathBoxY);

        // Move series selector
        int seriesBoxX = windowWidth - seriesBoxWidth - buttonWidth - 2 * UNIVERSAL_SPACER;
        int seriesBoxY = windowHeight - GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->seriesGroupBox->move(seriesBoxX, seriesBoxY);

        // Move name scheme selector
        int nameSchemeBoxX = windowWidth - nameSchemeBoxWidth - seriesBoxWidth - buttonWidth - 3 * UNIVERSAL_SPACER;
        int nameSchemeBoxY = windowHeight - GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->nameSchemeGroupBox->move(nameSchemeBoxX, nameSchemeBoxY);
    }

    // Move rename button
    int renameButtonX = windowWidth - buttonWidth - UNIVERSAL_SPACER;
    int renameButtonY = windowHeight - GROUPBOX_HEIGHT;
    ui->renameButton->move(renameButtonX, renameButtonY);

    // Resize table coloumns
    ui->episodeNameTable->setColumnWidth(0, episodeTableWidth*0.3);
    ui->episodeNameTable->setColumnWidth(1, episodeTableWidth*0.4);
    ui->episodeNameTable->setColumnWidth(2, episodeTableWidth*0.3);
}

void MainWindow::clearTable()
{
    ui->episodeNameTable->setStyleSheet(imageBackground);
    for (int i = tableRows; i>=0; i--)
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
        ui->episodeNameTable->setStyleSheet(whiteBackground);

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
