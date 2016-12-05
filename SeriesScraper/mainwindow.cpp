#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "languagedata.h"
#include "seriesparser.h"
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

    // Define minimum of the window size to display everything correctly
    int pathBoxWidth = ui->pathGroupBox->width();
    int seriesBoxWidth = ui->seriesGroupBox->width();
    int nameSchemeBoxWidth = ui->nameSchemeGroupBox->width();
    int buttonWidth = ui->renameButton->width();

    int upperWidth = seriesBoxWidth + nameSchemeBoxWidth + 3 * UNIVERSAL_SPACER;
    int lowerWidth = pathBoxWidth + buttonWidth + 3 * UNIVERSAL_SPACER;
    this->centralWidget()->setMinimumWidth(std::max(upperWidth, lowerWidth));

    setUpTable();
    setUpMenuBar();
    setUpRenameConfirmationMessageBox();

    // initialize view state
    ui->renameButton->setEnabled(false);
    ui->seasonComboBox->setEnabled(false);

    QObject::connect(ui->selectionButton, SIGNAL(clicked()), this, SLOT(openDirectory()));
    QObject::connect(ui->pathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(startSetPathTimer()));
    QObject::connect(setPathTimer, SIGNAL(timeout()), this, SLOT(setPath()));
    QObject::connect(ui->episodeNameTable, SIGNAL(cellActivated(int,int)), this, SLOT(onCellClicked(int,int)));
    QObject::connect(ui->seriesLineEdit, SIGNAL(textChanged(QString)), this, SLOT(startSeriesTextChangeTimer()));
    QObject::connect(seriesTextChangeTimer, SIGNAL(timeout()), this, SLOT(onSeriesTextChanged()));
    QObject::connect(ui->seasonComboBox, SIGNAL(activated(int)), this, SLOT(onSeasonChanged(int)));
    QObject::connect(ui->seriesLanguageComboBox, SIGNAL(activated(int)), this, SLOT(onSeriesLanguageChanged(int)));
    QObject::connect(ui->renameButton, SIGNAL(pressed()), this , SLOT(onRenameButtonPressed()));
    QObject::connect(disableSeriesProgressbarTimer, SIGNAL(timeout()), this, SLOT(disableSeriesProgressbar()));
    QObject::connect(progressBarTimer, SIGNAL(timeout()), this, SLOT(updateProgressbar()));
    QObject::connect(ui->nameSchemeComboBox, SIGNAL(activated(int)), this, SLOT(onNameSchemeChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete setPathTimer;
    delete seriesTextChangeTimer;
    delete progressBarTimer;
    delete disableSeriesProgressbarTimer;
    delete seriesStatusLabel;
    delete seriesProgressBar;
    delete blur;
    delete renameConfirmationMessageBox;
    delete helpMenu;
    delete aboutAction;
    delete settingsAction;
    delete fullScreenAction;
}

void MainWindow::setUpTable()
{
    // Set table start size
    ui->episodeNameTable->setColumnCount(2);

    // Set column width and name headers
    ui->episodeNameTable->setHorizontalHeaderLabels(QString("Original names;New names").split(";"));
    ui->episodeNameTable->horizontalHeader()->setStretchLastSection(true);

    // Set background
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
    seriesStatusLabel->setText("Not found");
    seriesStatusLabel->setMinimumWidth(200);
    seriesStatusLabel->setAlignment(Qt::AlignHCenter);
    seriesStatusLabel->setStyleSheet("color: rgb(255, 20, 20); "
                                     "font-weight: bold; "
                                     "font-size: 16px;");
    seriesStatusLabel->setHidden(true);
}

void MainWindow::setUpMenuBar()
{
    QString aboutText = "About " APPLICATIONNAME;

    viewMenu = new QMenu("Display");
    helpMenu = new QMenu("Help");

    aboutAction = new QAction(aboutText);
    settingsAction = new QAction("Settings");
    fullScreenAction = new QAction("Fullscreen");

    aboutAction->setMenuRole(QAction::ApplicationSpecificRole);
    settingsAction->setMenuRole(QAction::ApplicationSpecificRole);
    settingsAction->setShortcut(QKeySequence::Preferences);
    fullScreenAction->setShortcut(QKeySequence::FullScreen);

    helpMenu->addAction(aboutAction);
    viewMenu->addAction(settingsAction);
    viewMenu->addAction(fullScreenAction);

    ui->menuBar->addMenu(viewMenu);
    ui->menuBar->addMenu(helpMenu);

    // Connect Actions
    QObject::connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(showAboutDialog()));
    QObject::connect(settingsAction, SIGNAL(triggered(bool)), this, SLOT(showSettingsWindow()));
    QObject::connect(fullScreenAction, SIGNAL(triggered(bool)), this, SLOT(toggleFullScreen()));
    ui->episodeLineEdit->hide();
}

void MainWindow::setUpRenameConfirmationMessageBox()
{
    renameConfirmationMessageBox = new QMessageBox;
    renameConfirmationMessageBox->setWindowTitle("Are you sure?");
    renameConfirmationMessageBox->setText("The selected season seems to differ from the season found in your series directory. Do you really want to continue?");
    renameConfirmationMessageBox->addButton("Yes", QMessageBox::YesRole);
    renameConfirmationMessageBox->addButton("No", QMessageBox::NoRole);
    renameConfirmationMessageBox->setDefaultButton(QMessageBox::No);
}

void MainWindow::setSeriesAvailableStatus(bool status, bool isEmpty)
{
    if (isEmpty)
    {
        ui->seriesLineEdit->setStyleSheet(colorWhite);
        ui->correctSeriesLabel->setText("");
        setAmountSeasons(0);
        disableSeriesProgressbar();
    } else if(status)
    {
        ui->seriesLineEdit->setStyleSheet(colorGreen);
        ui->correctSeriesLabel->setText(checkmark);
        ui->seasonComboBox->setCurrentIndex(0);
    } else
    {
        ui->seriesLineEdit->setStyleSheet(colorRed);
        ui->correctSeriesLabel->setText(times);
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

    // Define size to differentiate bewteen layouts
    int bigSize = pathBoxWidth + seriesBoxWidth +  nameSchemeBoxWidth + buttonWidth + 5 * UNIVERSAL_SPACER;

    if (windowWidth >= bigSize) { // Representation for higher resolutions
        int spaceBetweenGroupboxes = (windowWidth - pathBoxWidth - seriesBoxWidth
                                      - nameSchemeBoxWidth - buttonWidth - 2 * UNIVERSAL_SPACER) / 3;

        // Resize table height
        int episodeTableHeight = windowHeight - GROUPBOX_HEIGHT - 2 * UNIVERSAL_SPACER;
        ui->episodeNameTable->setFixedSize(episodeTableWidth, episodeTableHeight);

        // Move series selector
        int seriesBoxX = UNIVERSAL_SPACER;
        int seriesBoxY = windowHeight - GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->seriesGroupBox->move(seriesBoxX, seriesBoxY);

        // Move name scheme selector
        int nameSchemeBoxX = UNIVERSAL_SPACER + seriesBoxWidth + spaceBetweenGroupboxes;
        int nameSchemeBoxY = windowHeight - GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->nameSchemeGroupBox->move(nameSchemeBoxX, nameSchemeBoxY);

        // Move path selector
        int pathBoxX = seriesBoxWidth + nameSchemeBoxWidth + UNIVERSAL_SPACER + 2 * spaceBetweenGroupboxes;
        int pathBoxY = windowHeight - GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->pathGroupBox->move(pathBoxX, pathBoxY);

        // Move rename button
        int renameButtonX = windowWidth - buttonWidth - UNIVERSAL_SPACER;
        int renameButtonY = windowHeight - GROUPBOX_HEIGHT;
        ui->renameButton->move(renameButtonX, renameButtonY);
    }
    else { // Standard representation
        int spaceBetweenUpperGroupboxes = (windowWidth - seriesBoxWidth
                                           - nameSchemeBoxWidth  - 2 * UNIVERSAL_SPACER) / 2;
        // Resize table height
        int episodeTableHeight = windowHeight - 2 * GROUPBOX_HEIGHT - 2 * UNIVERSAL_SPACER;
        ui->episodeNameTable->setFixedSize(episodeTableWidth, episodeTableHeight);

        // Move series selector
        int seriesBoxX = std::max(spaceBetweenUpperGroupboxes, UNIVERSAL_SPACER);
        int seriesBoxY = windowHeight - 2 * GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->seriesGroupBox->move(seriesBoxX, seriesBoxY);

        // Move name scheme selector
        int nameSchemeBoxX = seriesBoxX + seriesBoxWidth + UNIVERSAL_SPACER;
        int nameSchemeBoxY = windowHeight - 2 * GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->nameSchemeGroupBox->move(nameSchemeBoxX, nameSchemeBoxY);

        // Move path selector
        int pathBoxX = std::max(spaceBetweenUpperGroupboxes, UNIVERSAL_SPACER);
        int pathBoxY = windowHeight - GROUPBOX_HEIGHT - UNIVERSAL_SPACER;
        ui->pathGroupBox->move(pathBoxX, pathBoxY);

        // Move rename button
        int renameButtonX = nameSchemeBoxX + nameSchemeBoxWidth - buttonWidth;
        int renameButtonY = windowHeight - GROUPBOX_HEIGHT;
        ui->renameButton->move(renameButtonX, renameButtonY);
    }

    // Resize table coloumns
    ui->episodeNameTable->setColumnWidth(0, episodeTableWidth*0.45);
    ui->episodeNameTable->setColumnWidth(1, episodeTableWidth*0.47);

    // Resize series progressbar
    int seriesProgressbarWidth = episodeTableWidth / 2;
    seriesProgressBar->setFixedWidth(seriesProgressbarWidth);

    // Move series progressbar
    int episodeTableHeight = ui->episodeNameTable->height();
    int episodeTableX = ui->episodeNameTable->x();
    int episodeTableY = ui->episodeNameTable->y();

    // Move and resize episode edit
    //QTableWidgetItem* tableItem = ui->episodeNameTable->item(row, coloumn);
    //QRect position = ui->episodeNameTable->visualItemRect(tableItem;);
    //ui->episodeLineEdit->move(position.x() + 50, position.y() + 50);

    int seriesProgressbarX = episodeTableX + episodeTableWidth / 2 - seriesProgressBar->width() / 2;
    int seriesProgressbarY = episodeTableY + episodeTableHeight / 2 - seriesProgressBar->height() / 2;
    seriesProgressBar->move(seriesProgressbarX, seriesProgressbarY);

    // Move series failure text
    int seriesStatusLabelX = episodeTableX + episodeTableWidth / 2 - seriesStatusLabel->width() / 2;
    int seriesStatusLabelY = episodeTableY + episodeTableHeight / 2 + seriesProgressBar->height();
    seriesStatusLabel->move(seriesStatusLabelX, seriesStatusLabelY);
}

void MainWindow::updateView(QStringList oldFileNames, QStringList newFileNames, int amountSeasons)
{
    bool oldFileNamesAvaiable = !oldFileNames.empty();
    bool newFileNamesAvaiable = !newFileNames.empty();

    setAmountSeasons(amountSeasons);
    clearTable();

    int tableSize = std::max(newFileNames.size(), oldFileNames.size());
    // Fill up missing items
    while (newFileNames.size() < tableSize)
        newFileNames << "";
    while (oldFileNames.size() < tableSize)
        oldFileNames << "";
    // Fill table
    for (int i = 0; i < tableSize; i++) {
        setRow(i, oldFileNames.at(i), newFileNames.at(i));
    }
    if (oldFileNamesAvaiable && newFileNamesAvaiable) {
        for (int i = 0; i < tableSize; i++) {
            // Disable where not both entries exists
            if (oldFileNames.at(i).isEmpty())
                ui->episodeNameTable->item(i,1)->setTextColor(QColor(150, 150, 150));
            if (newFileNames.at(i).isEmpty())
                ui->episodeNameTable->item(i,0)->setTextColor(QColor(150, 150, 150));
        }
    }
}

void MainWindow::changeToDarkTheme()
{
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    colorWhite = "QLineEdit { background: rgb(25,25,25); }";
    colorGreen = "QLineEdit { background: rgb(4, 55, 4); }";
    colorRed = "QLineEdit { background: rgb(55, 15, 15); }";
    imageBackground = QString("background-image: url(:/images/logo.png); ")
            + QString("background-color: rgb(30, 30, 30);")
            + QString("background-repeat: no-repeat; ")
            + QString("background-attachment: fixed; ")
            + QString("background-position: center;");

    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    if (ui->episodeNameTable->itemAt(1,1) == NULL)
        clearTable();
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

void MainWindow::addNameSchemeItem(QString nameScheme)
{
    int recentAmount = ui->nameSchemeComboBox->count();

    if (!nameScheme.isEmpty()) {
        nameSchemeItemList << nameScheme;
        QString nameSchemeEntry = QString::number(++recentAmount) + ": " + nameScheme;
        ui->nameSchemeComboBox->addItem(nameSchemeEntry);
    }
}

void MainWindow::removeNameSchemeItem(int itemIndex)
{
    int recentAmount = ui->nameSchemeComboBox->count();

    // Discard impossible indexes
    if (itemIndex >= 0 && itemIndex < recentAmount) {
        nameSchemeItemList.removeAt(itemIndex);
        ui->nameSchemeComboBox->clear();

        // Add all remaining items again
        for (int i = 0; i < nameSchemeItemList.size(); i++) {
            QString nameSchemeEntry = QString::number(i + 1) + ": " + nameSchemeItemList.at(i);
            ui->nameSchemeComboBox->addItem(nameSchemeEntry);
        }
    }
}

void MainWindow::changeLocalization(QStringList translationList)
{
    QStringList tableHeader;
    tableHeader << translationList.at(LanguageData::oldName)
                << translationList.at(LanguageData::newName);

    ui->episodeNameTable->setHorizontalHeaderLabels(tableHeader);
    ui->pathGroupBox->setTitle(translationList.at(LanguageData::directorySelection));
    ui->selectionButton->setText(translationList.at(LanguageData::selection));
    ui->pathLabel->setText(translationList.at(LanguageData::path));
    ui->seriesGroupBox->setTitle(translationList.at(LanguageData::seriesSelection));
    ui->seriesLabel->setText(translationList.at(LanguageData::series));
    ui->seasonLabel->setText(translationList.at(LanguageData::season));
    ui->seriesLanguageLabel->setText(translationList.at(LanguageData::language));
    ui->nameSchemeGroupBox->setTitle(translationList.at(LanguageData::nameScheme));
    ui->renameButton->setText(translationList.at(LanguageData::rename));
    seriesStatusLabel->setText(translationList.at(LanguageData::notFound));
    viewMenu->setTitle(translationList.at(LanguageData::display));
    helpMenu->setTitle(translationList.at(LanguageData::help));
    aboutAction->setText(translationList.at(LanguageData::about) + " " + APPLICATIONNAME);
    settingsAction->setText(translationList.at(LanguageData::settings));
    fullScreenAction->setText(translationList.at(LanguageData::fullscreen));
    directorySelectionText = translationList.at(LanguageData::directorySelection);
    // Rename confirmation dialog
    renameConfirmationMessageBox->setWindowTitle(translationList.at(LanguageData::areYouSure));
    renameConfirmationMessageBox->setText(translationList.at(LanguageData::forceRename));
    renameConfirmationMessageBox->setButtonText(0, translationList.at(LanguageData::yes));
    renameConfirmationMessageBox->setButtonText(1, translationList.at(LanguageData::no));
}

void MainWindow::openDirectory()
{
    // Open directory-dialog to chose directory
    QString directoryPath;
    directoryPath = QFileDialog::getExistingDirectory(this, directorySelectionText, chosenPath.path());
    if (!directoryPath.isNull())
    {
        chosenPath = directoryPath; // Remember path
        ui->pathLineEdit->setText(directoryPath);
    }
}

void MainWindow::setPath()
{
    setPathTimer->stop();
    QString directoryPath = ui->pathLineEdit->text();
    QDir dir;
    dir.setPath(directoryPath);

    // Set the status
    if (dir.path().isEmpty()) {
        ui->pathLineEdit->setStyleSheet(colorWhite);
        ui->correctPathLabel->setText("");
    }
    else if (dir.exists()) {
        chosenPath = directoryPath;
        ui->pathLineEdit->setStyleSheet(colorGreen);
        ui->correctPathLabel->setText(checkmark);
    }
    else {
        ui->pathLineEdit->setStyleSheet(colorRed);
        ui->correctPathLabel->setText(times);
    }
    QString directory = dir.path();
    Message directoryChangedMsg;
    directoryChangedMsg.type = Message::view_changeDirectory_controller;
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

void MainWindow::onSeriesTextChanged()
{
    seriesTextChangeTimer->stop();
    QString seriesText = ui->seriesLineEdit->text();

    Message msg;
    msg.type = Message::view_changeSeriesText_controller;
    msg.data[0].qsPointer = &seriesText;
    msg.data[1].i = 1;
    emit sendMessage(msg);
}

void MainWindow::onSeasonChanged(int index)
{
    Message seasonChangedMsg;
    seasonChangedMsg.type = Message::view_changeSeason_controller;
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

void MainWindow::onNameSchemeChanged(int index)
{
    Message msgNameSchemeChanged;
    msgNameSchemeChanged.type = Message::view_changeNameScheme_controller;
    msgNameSchemeChanged.data[0].i = index;
    emit(sendMessage(msgNameSchemeChanged));
}

void MainWindow::showAboutDialog()
{
    Message msgShowAbout;
    msgShowAbout.type = Message::view_showAboutDialog_controller;
    emit(sendMessage(msgShowAbout));
}

void MainWindow::showSettingsWindow()
{
    Message msgShowSettings;
    msgShowSettings.type = Message::view_showSettingsWindow_controller;
    emit(sendMessage(msgShowSettings));
}

void MainWindow::toggleFullScreen()
{
    fullScreenEnabled = !fullScreenEnabled;

    if (fullScreenEnabled)
        this->showFullScreen();
    else
        this->showNormal();
}

void MainWindow::onSeriesLanguageChanged(int index)
{
    Message msgChangeSeriesLanguage;
    msgChangeSeriesLanguage.type = Message::view_changeSeriesLanguage_controller;
    msgChangeSeriesLanguage.data[0].i = index;
    emit(sendMessage(msgChangeSeriesLanguage));
}

void MainWindow::onCellClicked(int row, int coloumn)
{
    if (coloumn == 1) { // Only Episode names
        ui->episodeLineEdit->show();
        //qDebug() << position;
        //QWi
        QTableWidgetItem* tableItem = ui->episodeNameTable->item(row, coloumn);
        QRect position = ui->episodeNameTable->visualItemRect(tableItem);
        ui->episodeLineEdit->move(position.x() + 50, position.y() + 50);
        ui->episodeLineEdit->resize(position.width() - 200, position.height());


    }
}

void MainWindow::notify(Message &msg)
{
    switch (msg.type) {
    case Message::controller_updateView_view:
    {
        int amountSeasons = msg.data[0].i;
        QStringList oldFileNameList = *msg.data[1].qsListPointer;
        QStringList newFileNameList = *msg.data[2].qsListPointer;
        updateView(oldFileNameList, newFileNameList, amountSeasons);
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

        ui->selectionButton->setEnabled(false);

        break;
    }
    case Message::controller_addNameSchemes_view:
    {
        ui->nameSchemeComboBox->clear();
        QStringList nameSchemeList = *msg.data[0].qsListPointer;
        for (int i = 0; i < nameSchemeList.size(); i++)
            addNameSchemeItem(nameSchemeList.at(i));

        // Make sure even the largest item can be displayed on dropdown
        int minimumWidth = ui->nameSchemeComboBox->minimumSizeHint().width();
        ui->nameSchemeComboBox->view()->setMinimumWidth(minimumWidth);
        break;
    }
    case Message::controller_changeLocalization_view:
    {
        QStringList translationList = *msg.data[0].qsListPointer;
        changeLocalization(translationList);
        break;
    }
    case Message::controller_addSeriesLanguages_view:
    {
        QStringList seriesLanguageList = *msg.data[0].qsListPointer;
        for (int i = 0; i < seriesLanguageList.size(); i++)
            ui->seriesLanguageComboBox->addItem(seriesLanguageList.at(i));
        break;
    }
    case Message::controller_successSeriesLoading_view:
    {
        progressIncrement = 10;
        disableSeriesProgressbarTimer->start(200);
        ui->selectionButton->setEnabled(true);
        break;
    }
    case Message::controller_failureSeriesLoading_view:
    {
        seriesStatusLabel->setHidden(false);
        progressIncrement = 1;
        disableSeriesProgressbarTimer->start(2000);
        ui->selectionButton->setEnabled(true);
        break;
    }
    case Message::controller_seasonMismatch_view:
    {
        renameConfirmationMessageBox->show();
        renameConfirmationMessageBox->setFocus();
        if (renameConfirmationMessageBox->exec() == 0) // 0 = Yes button
        {
            Message msgForceRename;
            msgForceRename.type = Message::view_forceRename_controller;
            emit(sendMessage(msgForceRename));
        }
        ui->renameButton->setDown(false);
        break;
    }
    case Message::controller_setStatus_view:
    {
        QString status = *msg.data[0].qsPointer;
        ui->statusBar->showMessage(status, 10000);
        break;
    }
    case Message::controller_changeSeriesParser_view:
    {
        int selectedSeriesParser = msg.data[0].i;
        switch(selectedSeriesParser)
        {
        default:
        case SeriesParser::tmdb:
        {
            ui->seriesLanguageComboBox->setEnabled(true);
            break;
        }
        case SeriesParser::omdb:
        {
            ui->seriesLanguageComboBox->setEnabled(false);
            break;
        }
        }
        break;
    }
    case Message::controller_changeSeriesLanguage_view:
    {
        QString language = *msg.data[0].qsPointer;
        int indexOfLanguage = ui->seriesLanguageComboBox->findText(language);
        ui->seriesLanguageComboBox->setCurrentIndex(indexOfLanguage);
        break;
    }
    case Message::controller_changeNameScheme_view:
    {
        int nameSchemeIndex = msg.data[0].i;
        ui->nameSchemeComboBox->setCurrentIndex(nameSchemeIndex);
        break;
    }
    case Message::controller_setSeries_view:
    {
        QString series = *msg.data[0].qsPointer;
        int season = msg.data[1].i - 1;
        ui->seriesLineEdit->setText(series);
        ui->seasonComboBox->setCurrentIndex(season);
        seriesTextChangeTimer->stop(); // Avoid double loading
        break;
    }
    case Message::controller_setPath_view:
    {
        QString path = *msg.data[0].qsPointer;
        ui->pathLineEdit->setText(path);
        break;
    }
    case Message::controller_useDarkTheme_view:
    {
        changeToDarkTheme();
        // Workaround for white table headers
        setRow(0, "", "");
        clearTable();
        break;
    }
    default:
        break;
    }
}

bool MainWindow::setRow(int row, QString oldFileName, QString newFileName)
{
    // Check if trying to access rows, that are not existent and not the next possible new row
    if (row > tableRows)
        return false;
    else
        ui->episodeNameTable->setStyleSheet(whiteBackground);

    // Check if row items already exist to prevent multiple creations
    if (ui->episodeNameTable->item(row, 0) != NULL && ui->episodeNameTable->item(row, 1) != NULL) {
        ui->episodeNameTable->item(row, 0)->setText(oldFileName);
        ui->episodeNameTable->item(row, 1)->setText(newFileName);
    }
    else { // Not existing
        tableRows++;
        QTableWidgetItem *oldFile = new QTableWidgetItem(oldFileName);
        QTableWidgetItem *newFile = new QTableWidgetItem(newFileName);
        oldFile->setFlags(oldFile->flags() & ~Qt::ItemIsEditable);
        newFile->setFlags(newFile->flags() & ~Qt::ItemIsEditable);

        ui->episodeNameTable->setRowCount(tableRows);
        ui->episodeNameTable->setItem(row, 0, oldFile);
        ui->episodeNameTable->setItem(row, 1, newFile);
    }
    return true;
}
