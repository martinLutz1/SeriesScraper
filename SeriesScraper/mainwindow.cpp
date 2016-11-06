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
    tableRows(0),
    progressIncrement(1)
{
    ui->setupUi(this);
    setPathTimer = new QTimer(this);
    seriesTextChangeTimer = new QTimer(this);
    progressBarTimer = new QTimer(this);
    disableSeriesProgressbarTimer = new QTimer(this);
    seriesProgressBar = new QProgressBar(this);
    seriesStatusLabel = new QLabel(this);
    blur = new QGraphicsBlurEffect;

    // Table
    setUpTable();
    whiteBackground = ui->episodeNameTable->styleSheet();
    imageBackground = QString("background-image: url(:/images/logo.png); ")
            + QString("background-color: rgb(255, 255, 255);")
            + QString("background-repeat: no-repeat; ")
            + QString("background-attachment: fixed; ")
            + QString("background-position: center;");
    ui->episodeNameTable->setStyleSheet(imageBackground);

    // Table progressbar
    blur->setEnabled(false);
    ui->episodeNameTable->setGraphicsEffect(blur);
    seriesProgressBar->setHidden(true);

    // Table failure message
    seriesStatusLabel->setText("Nicht gefunden");
    seriesStatusLabel->setMinimumWidth(200);
    seriesStatusLabel->setAlignment(Qt::AlignHCenter);
    seriesStatusLabel->setStyleSheet("color: rgb(255, 20, 20); "
                                     "font-weight: bold; "
                                     "font-size: 16px;");
    seriesStatusLabel->setHidden(true);

    // Button
    ui->renameButton->setEnabled(false);

    // Season combobox
    ui->seasonComboBox->setEnabled(false);

    // Remove, when implemented!
    ui->nameSchemeComboBox->addItem("1: series - s*e* - ep.*");

    QObject::connect(ui->selectionButton, SIGNAL(clicked()), this, SLOT(openDirectory()));
    QObject::connect(ui->pathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(startSetPathTimer()));
    QObject::connect(setPathTimer, SIGNAL(timeout()), this, SLOT(setPath()));
    QObject::connect(ui->episodeNameTable, SIGNAL(cellChanged(int,int)), this, SLOT(onCellChange(int,int)));
    QObject::connect(ui->seriesLineEdit, SIGNAL(textChanged(QString)), this, SLOT(startSeriesTextChangeTimer()));
    QObject::connect(seriesTextChangeTimer, SIGNAL(timeout()), this, SLOT(onSeriesTextChange()));
    QObject::connect(ui->seasonComboBox, SIGNAL(activated(int)), this, SLOT(onSeasonChanged(int)));
    QObject::connect(ui->renameButton, SIGNAL(pressed()), this , SLOT(onRenameButtonPressed()));
    QObject::connect(disableSeriesProgressbarTimer, SIGNAL(timeout()), this, SLOT(disableSeriesProgressbar()));
    QObject::connect(progressBarTimer, SIGNAL(timeout()), this, SLOT(updateProgressbar()));
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
        progressIncrement = 10;
        disableSeriesProgressbarTimer->start(200);
    }
    else if (isEmpty) {
        ui->seriesLineEdit->setStyleSheet(colorWhite);
        ui->correctSeriesLabel->setText("");
        setAmountSeasons(0);
        clearTable();
        disableSeriesProgressbar();
    }
    else {
        ui->seriesLineEdit->setStyleSheet(colorRed);
        ui->correctSeriesLabel->setText(times);
        setAmountSeasons(0);
        clearTable();
        seriesStatusLabel->setHidden(false);
        progressIncrement = 1;
        disableSeriesProgressbarTimer->start(2000);
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
        // Resize table height
        int episodeTableHeight = windowHeight - 2 * GROUPBOX_HEIGHT - 3 * UNIVERSAL_SPACER;
        ui->episodeNameTable->setFixedSize(episodeTableWidth, episodeTableHeight);

        // Move path selector
        int pathBoxX = UNIVERSAL_SPACER;
        int pathBoxY = windowHeight - 2 * GROUPBOX_HEIGHT - 2 * UNIVERSAL_SPACER;
        ui->pathGroupBox->move(pathBoxX, pathBoxY);

        // Move series selector
        int seriesBoxX = pathBoxWidth + 2 * UNIVERSAL_SPACER;
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
        int seriesBoxX = windowWidth - seriesBoxWidth - nameSchemeBoxWidth - buttonWidth - 3 * UNIVERSAL_SPACER;
        int seriesBoxY = windowHeight - GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->seriesGroupBox->move(seriesBoxX, seriesBoxY);

        // Move name scheme selector
        int nameSchemeBoxX = windowWidth - nameSchemeBoxWidth - buttonWidth - 2 * UNIVERSAL_SPACER;
        int nameSchemeBoxY = windowHeight - GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->nameSchemeGroupBox->move(nameSchemeBoxX, nameSchemeBoxY);
    }

    // Move rename button
    int renameButtonX = windowWidth - buttonWidth - UNIVERSAL_SPACER;
    int renameButtonY = windowHeight - GROUPBOX_HEIGHT;
    ui->renameButton->move(renameButtonX, renameButtonY);

    // Resize table coloumns
    ui->episodeNameTable->setColumnWidth(0, episodeTableWidth*0.28);
    ui->episodeNameTable->setColumnWidth(1, episodeTableWidth*0.4);
    ui->episodeNameTable->setColumnWidth(2, episodeTableWidth*0.29);

    // Resize series progressbar
    int seriesProgressbarWidth = episodeTableWidth / 2;
    seriesProgressBar->setFixedWidth(seriesProgressbarWidth);

    // Move series progressbar
    int episodeTableHeight = ui->episodeNameTable->height();
    int episodeTableX = ui->episodeNameTable->x();
    int episodeTableY = ui->episodeNameTable->y();

    int seriesProgressbarX = episodeTableX + episodeTableWidth / 2 - seriesProgressBar->width() / 2;
    int seriesProgressbarY = episodeTableY + episodeTableHeight / 2 - seriesProgressBar->height() / 2;
    seriesProgressBar->move(seriesProgressbarX, seriesProgressbarY);

    // Move series failure text
    int seriesStatusLabelX = episodeTableX + episodeTableWidth / 2 - seriesStatusLabel->width() / 2;
    int seriesStatusLabelY = episodeTableY + episodeTableHeight / 2 + seriesProgressBar->height();
    seriesStatusLabel->move(seriesStatusLabelX, seriesStatusLabelY);
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

    // Disable or enable season selection
    bool enableSeasonComboBox = (amount != 0);
    ui->seasonComboBox->setEnabled(enableSeasonComboBox);
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

    // Set the status
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

    QString directory = dir.path();
    Message directoryChangedMsg;
    directoryChangedMsg.type = Message::view_directory_changed_controller;
    directoryChangedMsg.data[0].qsPointer = &directory;
    emit(sendMessage(directoryChangedMsg));
}

void MainWindow::startSetPathTimer()
{
    setPathTimer->start(500);
}

void MainWindow::startSeriesTextChangeTimer()
{
    seriesTextChangeTimer->start(1000);
}

void MainWindow::disableSeriesProgressbar()
{
    disableSeriesProgressbarTimer->stop();
    ui->episodeNameTable->setEnabled(true);
    seriesProgressBar->setHidden(true);
    seriesProgressBar->setValue(0);
    seriesStatusLabel->setHidden(true);
    blur->setEnabled(false);
    progressIncrement = 1;
}

void MainWindow::updateProgressbar()
{
    int progress = seriesProgressBar->value();
    progress += progressIncrement;
    if (progress > 100) {
        progress = 100;
        progressBarTimer->stop();
    }
    seriesProgressBar->setValue(progress);
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

    case Message::controller_enableButton_view:
    {
        bool enableButton = msg.data[0].b;
        ui->renameButton->setEnabled(enableButton);
        break;
    }

    case Message::controller_startSeriesLoading_view:
    {
        // Hide to avoid delay with blur
        ui->episodeNameTable->setHidden(true);
        blur->setEnabled(true);
        ui->episodeNameTable->setEnabled(false);
        ui->episodeNameTable->repaint();
        // Show after applying all effects and repainting
        ui->episodeNameTable->setHidden(false);
        seriesProgressBar->setValue(0);
        seriesProgressBar->setHidden(false);
        progressBarTimer->start(5);

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
