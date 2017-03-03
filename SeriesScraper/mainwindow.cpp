#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "languagedata.h"
#include "seriesparser.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QDesktopServices>
#include <QDebug>

#define UNIVERSAL_SPACER 10
#define GROUPBOX_HEIGHT 70
#define MINIMUM_WINDOW_WIDTH 870
#define MINIMUM_PATH_STRUCTURE_BOX_SIZE 150

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    chosenPath(QDir::homePath()),
    progressIncrement(1)
{
    ui->setupUi(this);
    seriesTextChangeTimer = new QTimer(this);
    clearStatusTextTimer = new QTimer(this);
    hideRenameProgressTimer = new QTimer(this);
    statusBarTypeImageLabel = new QLabel();
    shadow = new CustomShadowEffect(ui->renameProgressScrollArea);
    progressIndicatorPath = new QProgressIndicator;
    progressIndicatorSeries = new QProgressIndicator;

    pathStructureComboBoxList[0] = ui->pathStructure1ComboBox;
    pathStructureComboBoxList[1] = ui->pathStructure2ComboBox;
    pathStructureComboBoxList[2] = ui->pathStructure3ComboBox;
    pathStructureComboBoxList[3] = ui->pathStructure4ComboBox;

    setUpTable();
    setUpMenuBar();
    setUpConfirmationMessageBoxes();
    setUpDirectoryWidget();
    setUpRenameProgressWidget();
    setUpGUI();

    QObject::connect(ui->selectionButton, SIGNAL(clicked(bool)), this, SLOT(openDirectory()));
    QObject::connect(ui->directoryUpdateButton, SIGNAL(clicked(bool)), this, SLOT(onUpdateDirectory()));
    QObject::connect(ui->seriesLineEdit, SIGNAL(textChanged(QString)), this, SLOT(startSeriesTextChangeTimer()));
    QObject::connect(seriesTextChangeTimer, SIGNAL(timeout()), this, SLOT(onSeriesTextChanged()));
    QObject::connect(ui->seasonComboBox, SIGNAL(activated(int)), this, SLOT(onSeasonChanged(int)));
    QObject::connect(ui->seriesLanguageComboBox, SIGNAL(activated(int)), this, SLOT(onSeriesLanguageChanged(int)));
    QObject::connect(ui->renameButton, SIGNAL(clicked(bool)), this , SLOT(onRenameButtonPressed()));
    QObject::connect(ui->nameSchemeComboBox, SIGNAL(activated(int)), this, SLOT(onNameSchemeChanged(int)));
    QObject::connect(clearStatusTextTimer, SIGNAL(timeout()), this, SLOT(clearStatusText()));
    QObject::connect(ui->episodeNameTable, SIGNAL(cellChanged(int,int)), this, SLOT(onTableEntryChanged(int,int)));
    QObject::connect(hideRenameProgressTimer, SIGNAL(timeout()), this, SLOT(slideOutRenameProgressWidget()));
    QObject::connect(renameSlideProgressAnimation, SIGNAL(finished()), this, SLOT(hideRenameProgressWidget()));
}

MainWindow::~MainWindow()
{
    QRect windowRect = this->geometry();
    Message msgSetWindowRect;
    msgSetWindowRect.type = Message::view_setWindowRect_controller;
    msgSetWindowRect.data[0].qRectPointer = &windowRect;
    emit(sendMessage(msgSetWindowRect));

    delete ui;
    delete seriesTextChangeTimer;
    delete clearStatusTextTimer;
    delete hideRenameProgressTimer;
    delete statusBarTypeImageLabel;
    delete shadow;
    delete renameSlideProgressAnimation;
    delete renameConfirmationMessageBox;
    delete posterConfirmationMessageBox;
    delete fileMenu;
    delete helpMenu;
    delete directoryEntriesMenu;
    delete savePosterAction;
    delete aboutAction;
    delete settingsAction;
    delete fullScreenAction;
    delete progressIndicatorPath;
    delete progressIndicatorSeries;
    for (int i = 0; i < NUMBER_PATH_STRUCTURE_COMBOBOXES; i++)
        delete pathStructureComboBoxList[i];
}

void MainWindow::disableGUIControl()
{
    ui->centralControlElementWidget->setEnabled(false);
}

void MainWindow::enableGUIControl()
{
    ui->centralControlElementWidget->setEnabled(true);
}

void MainWindow::setUpGUI()
{
    statusBarTypeImageLabel->setTextFormat(Qt::RichText);
    this->statusBar()->addWidget(statusBarTypeImageLabel);
    ui->seriesLineEditHorizontalLayout->addWidget(progressIndicatorSeries);

    this->centralWidget()->setMinimumWidth(MINIMUM_WINDOW_WIDTH);

    ui->seriesInfohorizontalLayout->setStretch(0, 3);
    ui->seriesInfohorizontalLayout->setStretch(1, 1);
    ui->seriesSelectionHorizontalLayout->setStretch(0, 8);
    ui->seriesSelectionHorizontalLayout->setStretch(1, 2);
    ui->seriesSelectionHorizontalLayout->setStretch(2, 3);
    ui->seriesSelectionHorizontalLayout->setStretch(3, 4);

    ui->infoGroupBox->setLayout(ui->seriesInfohorizontalLayout);
    ui->pathGroupBox->setLayout(ui->directorySelectionHorizontalLayout);
    ui->seriesGroupBox->setLayout(ui->seriesSelectionHorizontalLayout);
    ui->centralControlElementWidget->setLayout(ui->controlElementshorizontalLayout);

    // Add icons
    window()->setWindowIcon(QIcon(":/images/logo.png"));
    settingsAction->setIcon(QIcon(":/images/settings.png"));
    aboutAction->setIcon(QIcon(":/images/about.png"));
    savePosterAction->setIcon(QIcon(":/images/save.png"));
    undoRenameAction->setIcon(QIcon(":/images/undo.png"));
    fullScreenAction->setIcon(QIcon(":/images/fullscreen.png"));

    // Initialize view state
    ui->renameButton->setEnabled(false);
    savePosterAction->setEnabled(false);
    undoRenameAction->setEnabled(false);
    ui->seasonComboBox->setEnabled(false);
    ui->additionalInfoScrollArea->hide();

    this->activateWindow();
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
}

void MainWindow::setUpMenuBar()
{
    QString aboutText = "About " APPLICATIONNAME;

    fileMenu = new QMenu("File");
    viewMenu = new QMenu("Display");
    helpMenu = new QMenu("Help");

    savePosterAction = new QAction("Save poster");
    undoRenameAction = new QAction("Undo renaming");
    aboutAction = new QAction(aboutText);
    settingsAction = new QAction("Settings");
    fullScreenAction = new QAction("Fullscreen");

    aboutAction->setMenuRole(QAction::ApplicationSpecificRole);
    settingsAction->setMenuRole(QAction::ApplicationSpecificRole);

    settingsAction->setShortcut(QKeySequence::Preferences);
    fullScreenAction->setShortcut(QKeySequence::FullScreen);
    savePosterAction->setShortcut(QKeySequence::Save);
    undoRenameAction->setShortcut(QKeySequence::Undo);

    fileMenu->addAction(savePosterAction);
    fileMenu->addAction(undoRenameAction);
    helpMenu->addAction(aboutAction);
    fileMenu->addAction(settingsAction);
    viewMenu->addAction(fullScreenAction);

    ui->menuBar->addMenu(fileMenu);
    ui->menuBar->addMenu(viewMenu);
    ui->menuBar->addMenu(helpMenu);

    // Connect Actions
    QObject::connect(savePosterAction, SIGNAL(triggered(bool)), this, SLOT(savePoster()));
    QObject::connect(undoRenameAction, SIGNAL(triggered(bool)), this, SLOT(undoRenaming()));
    QObject::connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(showAboutDialog()));
    QObject::connect(settingsAction, SIGNAL(triggered(bool)), this, SLOT(showSettingsWindow()));
    QObject::connect(fullScreenAction, SIGNAL(triggered(bool)), this, SLOT(toggleFullScreen()));
}

void MainWindow::setUpConfirmationMessageBoxes()
{
    renameConfirmationMessageBox = new QMessageBox;
    renameConfirmationMessageBox->setWindowTitle("Are you sure?");
    renameConfirmationMessageBox->setText("The selected season seems to differ from the season found in your series directory. Do you really want to continue?");
    renameConfirmationMessageBox->addButton("Yes", QMessageBox::YesRole);
    renameConfirmationMessageBox->addButton("No", QMessageBox::NoRole);
    renameConfirmationMessageBox->setDefaultButton(QMessageBox::No);

    posterConfirmationMessageBox = new QMessageBox;
    posterConfirmationMessageBox->setWindowTitle("Override poster?");
    posterConfirmationMessageBox->setText("A poster already exists in your series directory. Do you want to override it?");
    posterConfirmationMessageBox->addButton("Yes", QMessageBox::YesRole);
    posterConfirmationMessageBox->addButton("No", QMessageBox::NoRole);
    posterConfirmationMessageBox->setDefaultButton(QMessageBox::No);

    undoRenameConfirmationBox = new QMessageBox;
    undoRenameConfirmationBox->setWindowTitle("Undo renaming");
    undoRenameConfirmationBox->setText("Are you sure you want to undo the last rename action?");
    undoRenameConfirmationBox->addButton("Yes", QMessageBox::YesRole);
    undoRenameConfirmationBox->addButton("No", QMessageBox::NoRole);
    undoRenameConfirmationBox->setDefaultButton(QMessageBox::No);
}

void MainWindow::setUpDirectoryWidget()
{
    ui->directoryWidgetHorizontalLayout->addWidget(progressIndicatorPath);
    directoryEntriesMenu = new QMenu(this);

    QObject::connect(ui->pathStructureContentButton, SIGNAL(clicked()), this, SLOT(onPathStructureContentButtonClicked()));
    QObject::connect(directoryEntriesMenu, SIGNAL(triggered(QAction*)), this, SLOT(onDirectoryEntryClicked(QAction*)));
    QObject::connect(ui->pathStructure1ComboBox, SIGNAL(activated(int)), this, SLOT(onDirectoryComboBox1EntryClicked(int)));
    QObject::connect(ui->pathStructure2ComboBox, SIGNAL(activated(int)), this, SLOT(onDirectoryComboBox2EntryClicked(int)));
    QObject::connect(ui->pathStructure3ComboBox, SIGNAL(activated(int)), this, SLOT(onDirectoryComboBox3EntryClicked(int)));
    QObject::connect(ui->pathStructure4ComboBox, SIGNAL(activated(int)), this, SLOT(onDirectoryComboBox4EntryClicked(int)));

    ui->pathStructure3ComboBox->setVisible(false);
    ui->pathStructure4ComboBox->setVisible(false);

    for (int i = 0; i < NUMBER_PATH_STRUCTURE_COMBOBOXES; i++)
    {
        pathStructureComboBoxList[i]->setEnabled(false);
    }
    ui->directoryUpdateButton->setEnabled(false);
    ui->pathStructureContentButton->setEnabled(false);
}

void MainWindow::setUpRenameProgressWidget()
{
    ui->renameProgressWidget->setLayout(ui->renamingProgressVerticalLayout);
    ui->renamingProgressBar->setMinimum(0);

    shadow->setBlurRadius(40.0);
    shadow->setDistance(6.0);
    shadow->setColor(QColor(0, 0, 0, 150));

    renameSlideProgressAnimation = new QPropertyAnimation(ui->renameProgressScrollArea, "geometry");
    renameSlideProgressAnimation->setDuration(400);

    ui->renameProgressScrollArea->hide();
    ui->renameProgressScrollArea->setGraphicsEffect(shadow);
}

void MainWindow::setSeriesAvailableStatus(bool status, bool isEmpty)
{
    if (isEmpty)
    {
        ui->seriesLineEdit->setStyleSheet(colorWhite);
        ui->correctSeriesLabel->hide();
        progressIndicatorSeries->show();
        progressIndicatorSeries->stopAnimation();
    } else if (status)
    {
        ui->seriesLineEdit->setStyleSheet(colorGreen);
        ui->correctSeriesLabel->setPixmap(QPixmap(":/images/check-20.png"));
        hideSeriesLoadingAnimation();
    } else
    {
        ui->seriesLineEdit->setStyleSheet(colorRed);
        ui->correctSeriesLabel->setPixmap(QPixmap(":/images/error-20.png"));
        hideSeriesLoadingAnimation();
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    int windowHeight = this->centralWidget()->height();
    int windowWidth = this->centralWidget()->width();
    int episodeTableWidth = windowWidth - 2 * UNIVERSAL_SPACER;
    int episodeTableX = UNIVERSAL_SPACER;
    int controlHeight = ui->centralControlElementWidget->height();
    int episodeTableHeight = windowHeight - 3 * UNIVERSAL_SPACER - controlHeight;
    int controlWidth = windowWidth - 2 * UNIVERSAL_SPACER;
    int controlY = episodeTableX + episodeTableHeight + UNIVERSAL_SPACER;
    int renameProgressWidgetWidth = ui->renameProgressScrollArea->width();
    int renameProgressWidgetX = (episodeTableWidth - renameProgressWidgetWidth) / 2;

    if (seriesInformationEnabled)
    {
        episodeTableWidth = 0.77 * (windowWidth - 2 * UNIVERSAL_SPACER);
        renameProgressWidgetX = (episodeTableWidth - renameProgressWidgetWidth) / 2;
        int additionalInfoWidth = 0.23 * (windowWidth - 2 * UNIVERSAL_SPACER);
        int additionalInfoHeight = episodeTableHeight;

        if (additionalInfoWidth > 250)
        {
            additionalInfoWidth = 250;
            episodeTableWidth = windowWidth - 2 * UNIVERSAL_SPACER - additionalInfoWidth;
        }
        int imageLabelWidth = additionalInfoWidth - 2 * UNIVERSAL_SPACER;
        int imageLabelHeight = additionalInfoHeight * 0.6;

        // Scale before further movements to make sure we have the correct image size
        ui->posterInfoLabel->setPixmap(seriesImage.scaled(imageLabelWidth, imageLabelHeight, Qt::KeepAspectRatio));
        ui->posterInfoLabel->setFixedSize(ui->posterInfoLabel->pixmap()->size());

        int additionalInfoX = episodeTableX + episodeTableWidth - 1;
        int additionalInfoY = UNIVERSAL_SPACER;
        int imageLabelX = std::max(UNIVERSAL_SPACER, additionalInfoWidth / 2 - ui->posterInfoLabel->pixmap()->width() / 2);
        int imageLabelY = UNIVERSAL_SPACER;
        int seriesNameX = (additionalInfoWidth - ui->seriesNameInfoLabelData->sizeHint().width()) / 2;
        int seriesNameY = ui->posterInfoLabel->y() + ui->posterInfoLabel->height() + UNIVERSAL_SPACER;
        int infoBoxY = seriesNameY + ui->seriesNameInfoLabelData->height() + 2 * UNIVERSAL_SPACER;

        // Resize
        ui->additionalInfoScrollArea->setFixedSize(additionalInfoWidth, additionalInfoHeight);
        ui->infoGroupBox->setFixedSize(additionalInfoWidth - 2 * UNIVERSAL_SPACER, ui->infoGroupBox->height());

        // Move
        ui->additionalInfoScrollArea->move(additionalInfoX, additionalInfoY);
        ui->posterInfoLabel->move(imageLabelX, imageLabelY);
        ui->infoGroupBox->move(UNIVERSAL_SPACER, infoBoxY);
        ui->seriesNameInfoLabelData->move(seriesNameX, seriesNameY);
    }

    // Move
    ui->centralControlElementWidget->move(UNIVERSAL_SPACER, controlY);
    ui->renameProgressScrollArea->move(renameProgressWidgetX, ui->renameProgressScrollArea->y());

    //Resize
    ui->episodeNameTable->setFixedSize(episodeTableWidth, episodeTableHeight);
    ui->episodeNameTable->setColumnWidth(0, episodeTableWidth*0.45);
    ui->episodeNameTable->setColumnWidth(1, episodeTableWidth*0.47);
    ui->additionalInfoScrollArea->setFixedHeight(episodeTableHeight);
    ui->centralControlElementWidget->setFixedWidth(controlWidth);

    updateDirectoryWidgetVisibility();
}

void MainWindow::updateView(QStringList oldFileNames, QStringList newFileNames, int amountSeasons)
{
    bool useColorization = (oldFileNames.empty() || newFileNames.isEmpty());
    int tableSize = std::max(newFileNames.size(), oldFileNames.size());

    setAmountSeasons(amountSeasons);

    // Fill up missing items
    while (newFileNames.size() < tableSize)
        newFileNames << "";
    while (oldFileNames.size() < tableSize)
        oldFileNames << "";
    // Fill table
    for (int i = 0; i < tableSize; i++)
        updateRow(i, oldFileNames.at(i), newFileNames.at(i), useColorization);

    // Tidy up what is left of unnecessary entries
    ui->episodeNameTable->setRowCount(tableSize);

    for (int i = ui->episodeNameTable->rowCount(); i >= tableSize; i--)
        ui->episodeNameTable->removeRow(i);
}

void MainWindow::updateDirectoryWidget(std::vector<QStringList> pathStructure, bool containsRoot, QString path)
{
    clearDirectoryWidget();
    if (pathStructure.size() == 0)
        return;

    for (int i = 0; i < pathStructure.at(0).size(); i++)
    {
        directoryEntriesMenu->addAction(QIcon(":/images/folder.png"), pathStructure.at(0).at(i));
    }
    // Add open directory entry
    directoryEntriesMenu->addSeparator();
    directoryEntriesMenu->addAction(QIcon(":/images/folder_video.png"), openThisFolderText);

    // Fill comboboxes
    for (int i = 0; i < int(pathStructure.size() - 2); i++)
    {
        for (int j = 0; j < pathStructure.at(i + 1).size(); j++)
        {
            if (containsRoot && (int(pathStructure.size() - 3) == i))
            {
                pathStructureComboBoxList[i]->addItem(QIcon(":/images/hdd.png"), pathStructure.at(i + 1).at(j));
            }
            else
            {
                pathStructureComboBoxList[i]->addItem(QIcon(":/images/folder.png"), pathStructure.at(i + 1).at(j));
            }
        }
        pathStructureComboBoxList[i]->setCurrentIndex(pathStructure.at(pathStructure.size() - 1).at(i).toInt());
    }

    // Set accessability of widget
    for (int i = 0; i < NUMBER_PATH_STRUCTURE_COMBOBOXES; i++)
    {
        pathStructureComboBoxList[i]->setEnabled(pathStructureComboBoxList[i]->count() > 0);
    }
    ui->pathStructureContentButton->setEnabled(pathStructure.size() > NUMBER_PATH_STRUCTURE_COMBOBOXES - 1);

    QDir dir(path);
    if (dir.exists() && !path.isEmpty())
    {
        chosenPath = path;
        ui->directoryUpdateButton->setEnabled(true);
    }
    else
    {
        chosenPath = QDir::homePath();
    }
}

void MainWindow::clearDirectoryWidget()
{
    directoryEntriesMenu->clear();
    for (int i = 0; i < NUMBER_PATH_STRUCTURE_COMBOBOXES; i++)
        pathStructureComboBoxList[i]->clear();
}

void MainWindow::updateDirectoryWidgetVisibility()
{
    int layoutWidth = ui->centralWidget->width() - 605;
    ui->pathStructure3ComboBox->setVisible(layoutWidth >= 600);
    ui->pathStructure4ComboBox->setVisible(layoutWidth >= 720);
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
    shadow->setColor(QColor(255, 255, 255, 150));

    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    if (ui->episodeNameTable->itemAt(1,1) == NULL)
        clearTable();
}

void MainWindow::showSeriesLoadingAnimation()
{
    progressIndicatorSeries->startAnimation();
    ui->correctSeriesLabel->hide();
    progressIndicatorSeries->show();
}

void MainWindow::hideSeriesLoadingAnimation()
{
    progressIndicatorSeries->stopAnimation();
    progressIndicatorSeries->hide();
    ui->correctSeriesLabel->show();
}

void MainWindow::showRenameProgress()
{
    int renameProgressWidgetWidth = ui->renameProgressScrollArea->width();
    int renameProgressWidgetHeight = ui->renameProgressScrollArea->height();
    int renameProgressWidgetX = ui->renameProgressScrollArea->x();
    renameSlideProgressAnimation->setStartValue(QRect(renameProgressWidgetX, (-1)*(renameProgressWidgetHeight), renameProgressWidgetWidth, renameProgressWidgetHeight));
    renameSlideProgressAnimation->setEndValue(QRect(renameProgressWidgetX, -1, renameProgressWidgetWidth, renameProgressWidgetHeight));

    isRenameProgressHiding = false;
    renameSlideProgressAnimation->start();
    ui->renameProgressScrollArea->show();
}

void MainWindow::hideRenameProgress()
{
    hideRenameProgressTimer->start(1500);
}

void MainWindow::updateRenameProgress(int amountFiles, int currentFile, QString oldFileName)
{
    if (ui->renamingProgressBar->maximum() != amountFiles)
        ui->renamingProgressBar->setMaximum(amountFiles);
    ui->renamingProgressBar->setValue(currentFile);

    ui->renamingProgressCurrentObjectLabel->setText(QString::number(currentFile));
    ui->renamingProgressTotalObjectsLabel->setText(QString::number(amountFiles));

    QFontMetrics fm(ui->renamingProgressCurrentFileLabel->font());
    bool chopedOff = false;
    int currentFileTextWidth = fm.width(oldFileName);
    while (currentFileTextWidth >= ui->renameProgressScrollArea->width() - ui->renamingProgressFileOutputLabel->width() - 4 * 10)
    {
        oldFileName.chop(2);
        currentFileTextWidth = fm.width(oldFileName);
        chopedOff = true;
    }
    if (chopedOff)
        oldFileName += "...";
    ui->renamingProgressCurrentFileLabel->setText(oldFileName);
}

void MainWindow::clearTable()
{
    ui->episodeNameTable->setStyleSheet(imageBackground);
    for (int i = ui->episodeNameTable->rowCount(); i >= 0; i--)
        ui->episodeNameTable->removeRow(i);
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
    int currentAmount = ui->nameSchemeComboBox->count();
    int selectedIndex = ui->nameSchemeComboBox->currentIndex();

    // Discard impossible indexes
    if (itemIndex >= 0 && itemIndex < currentAmount) {
        nameSchemeItemList.removeAt(itemIndex);
        ui->nameSchemeComboBox->clear();

        // Add all remaining items again
        for (int i = 0; i < nameSchemeItemList.size(); i++) {
            QString nameSchemeEntry = QString::number(i + 1) + ": " + nameSchemeItemList.at(i);
            ui->nameSchemeComboBox->addItem(nameSchemeEntry);
        }
    }
    // Set selected name scheme back to old selection, if possible
    if (selectedIndex < itemIndex)
        ui->nameSchemeComboBox->setCurrentIndex(selectedIndex);
    else if (selectedIndex > itemIndex && selectedIndex <= currentAmount - 1)
        ui->nameSchemeComboBox->setCurrentIndex(selectedIndex - 1);
}

void MainWindow::setStatusMessage(QString message, int type)
{
    clearStatusTextTimer->stop();
    QString labelText;
    switch (type)
    {
    case statusMessageType::error:
    {
        labelText = "<img src=:/images/error.png> ";
        break;
    }
    case statusMessageType::success:
    {
        labelText = "<img src=:/images/check.png> ";
        break;
    }
    case statusMessageType::info:
    {
        labelText = "";
        break;
    }
    }
    labelText += message;
    statusBarTypeImageLabel->setText(labelText);
    clearStatusTextTimer->start(5000);
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
    ui->nameSchemeLabel->setText(translationList.at(LanguageData::nameScheme));
    ui->renameButton->setText(translationList.at(LanguageData::rename));
    // Menubar
    fileMenu->setTitle(translationList.at(LanguageData::file));
    viewMenu->setTitle(translationList.at(LanguageData::display));
    helpMenu->setTitle(translationList.at(LanguageData::help));
    aboutAction->setText(translationList.at(LanguageData::about) + " " + APPLICATIONNAME);
    settingsAction->setText(translationList.at(LanguageData::settings));
    savePosterAction->setText(translationList.at(LanguageData::savePoster));
    undoRenameAction->setText(translationList.at(LanguageData::undoRenaming));
    fullScreenAction->setText(translationList.at(LanguageData::fullscreen));
    // Info sidebar
    ui->airDateInfoLabel->setText(translationList.at(LanguageData::airDate) + ":");
    ui->seasonInfoLabel->setText(translationList.at(LanguageData::season) + ":");
    ui->totalEpisodesInfoLabel->setText(translationList.at(LanguageData::episodeNumber) + ":");
    // Rename confirmation dialog
    renameConfirmationMessageBox->setWindowTitle(translationList.at(LanguageData::areYouSure));
    renameConfirmationMessageBox->setText(translationList.at(LanguageData::forceRename));
    renameConfirmationMessageBox->setButtonText(0, translationList.at(LanguageData::yes));
    renameConfirmationMessageBox->setButtonText(1, translationList.at(LanguageData::no));
    // Poster confirmation dialog
    posterConfirmationMessageBox->setWindowTitle(translationList.at(LanguageData::overridePoster));
    posterConfirmationMessageBox->setText(translationList.at(LanguageData::posterAlreadyExists));
    posterConfirmationMessageBox->setButtonText(0, translationList.at(LanguageData::yes));
    posterConfirmationMessageBox->setButtonText(1, translationList.at(LanguageData::no));
    // Undo renaming confirmation dialog
    undoRenameConfirmationBox->setWindowTitle(translationList.at(LanguageData::undoRenaming));
    undoRenameConfirmationBox->setText(translationList.at(LanguageData::undoRenamingDetailed));
    undoRenameConfirmationBox->setButtonText(0, translationList.at(LanguageData::yes));
    undoRenameConfirmationBox->setButtonText(1, translationList.at(LanguageData::no));
    // Misc
    directorySelectionText = translationList.at(LanguageData::directorySelection);
    openThisFolderText = translationList.at(LanguageData::openThisFolder);
}

void MainWindow::openDirectory()
{
    // Open directory-dialog to chose directory
    QString directoryPath;
    directoryPath = QFileDialog::getExistingDirectory(this, directorySelectionText, chosenPath.path());
    QDir dir(directoryPath);

    if (!directoryPath.isNull() && dir.exists())
    {
        chosenPath = directoryPath;
        ui->directoryUpdateButton->setEnabled(true);

        Message directoryChangedMsg;
        directoryChangedMsg.type = Message::view_changeDirectory_controller;
        directoryChangedMsg.data[0].qsPointer = &directoryPath;
        emit(sendMessage(directoryChangedMsg));
    }
}


void MainWindow::onUpdateDirectory()
{
    Message directoryUpdateMsg;
    directoryUpdateMsg.type = Message::view_updateDirectory_controller;
    emit(sendMessage(directoryUpdateMsg));
}

void MainWindow::startSeriesTextChangeTimer()
{
    seriesTextChangeTimer->start(700);
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

void MainWindow::onTableEntryChanged(int row, int coloumn)
{
    int selectedRow = ui->episodeNameTable->currentRow();
    if (selectedRow == row && coloumn == 1)
    {
        QString newFileName = ui->episodeNameTable->item(row, coloumn)->text();

        Message msgChangeNewFileName;
        msgChangeNewFileName.type = Message::view_changeNewFileName_controller;
        msgChangeNewFileName.data[0].i = row;
        msgChangeNewFileName.data[1].qsPointer = &newFileName;
        emit(sendMessage(msgChangeNewFileName));
    }
}

void MainWindow::onDirectoryEntryClicked(QAction *clickedAction)
{
    QString selectedText = clickedAction->text();

    for (int i = 0; i < directoryEntriesMenu->actions().size(); i++)
    {
        if (directoryEntriesMenu->actions().at(i)->text() == selectedText)
        {
            // Last entry open current directory
            if (directoryEntriesMenu->actions().size() - 1 == i)
            {
                QDesktopServices::openUrl(QUrl::fromLocalFile(chosenPath.absolutePath()));
                break;
            }
            onDirectoryComboBoxEntryClicked(0, i);
            break;
        }
    }
}

void MainWindow::onDirectoryComboBox1EntryClicked(int selection)
{
    onDirectoryComboBoxEntryClicked(1, selection);
}

void MainWindow::onDirectoryComboBox2EntryClicked(int selection)
{
    onDirectoryComboBoxEntryClicked(2, selection);
}

void MainWindow::onDirectoryComboBox3EntryClicked(int selection)
{
    onDirectoryComboBoxEntryClicked(3, selection);
}

void MainWindow::onDirectoryComboBox4EntryClicked(int selection)
{
    onDirectoryComboBoxEntryClicked(4, selection);
}

void MainWindow::onDirectoryComboBoxEntryClicked(int level, int selection)
{
    Message msgSwitchToFolder;
    msgSwitchToFolder.type = Message::view_switchToDirectory_controller;
    msgSwitchToFolder.data[0].i = level;
    msgSwitchToFolder.data[1].i = selection;
    emit(sendMessage(msgSwitchToFolder));
}

void MainWindow::clearStatusText()
{
    clearStatusTextTimer->stop();
    statusBarTypeImageLabel->clear();
}

void MainWindow::savePoster()
{
    Message msgSavePoster;
    msgSavePoster.type = Message::view_savePoster_controller;
    emit(sendMessage(msgSavePoster));
}

void MainWindow::undoRenaming()
{
    undoRenameConfirmationBox->show();
    undoRenameConfirmationBox->buttons().at(1)->setFocus();
    if (undoRenameConfirmationBox->exec() == 0) // 0 = Yes button
    {
        Message msgUndoRenaming;
        msgUndoRenaming.type = Message::view_undoRenaming_controller;
        emit(sendMessage(msgUndoRenaming));
    }
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

void MainWindow::onPathStructureContentButtonClicked()
{
    directoryEntriesMenu->exec(QCursor::pos());
}

void MainWindow::slideOutRenameProgressWidget()
{
    hideRenameProgressTimer->stop();
    isRenameProgressHiding = true;

    int renameProgressWidgetWidth = ui->renameProgressScrollArea->width();
    int renameProgressWidgetHeight = ui->renameProgressScrollArea->height();
    int renameProgressWidgetX = ui->renameProgressScrollArea->x();
    int renameProgressWidgetY = ui->renameProgressScrollArea->y();

    renameSlideProgressAnimation->setStartValue(QRect(renameProgressWidgetX, renameProgressWidgetY, renameProgressWidgetWidth, renameProgressWidgetHeight));
    renameSlideProgressAnimation->setEndValue(QRect(renameProgressWidgetX, (-1)*renameProgressWidgetHeight, renameProgressWidgetWidth, renameProgressWidgetHeight));
    renameSlideProgressAnimation->start();
}

void MainWindow::hideRenameProgressWidget()
{
    if (isRenameProgressHiding)
    {
        ui->renameProgressScrollArea->hide();
        updateRenameProgress(0, 0, "");
    }
}

void MainWindow::onSeriesLanguageChanged(int index)
{
    Message msgChangeSeriesLanguage;
    msgChangeSeriesLanguage.type = Message::view_changeSeriesLanguage_controller;
    msgChangeSeriesLanguage.data[0].i = index;
    emit(sendMessage(msgChangeSeriesLanguage));
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
    case Message::controller_enableRenameButton_view:
    {
        bool enableButton = msg.data[0].b;
        ui->renameButton->setEnabled(enableButton);
        break;
    }
    case Message::controller_enableSavePoster_view:
    {
        bool savePoster = msg.data[0].b;
        savePosterAction->setEnabled(savePoster);
        break;
    }
    case Message::controller_startSeriesLoading_view:
    {
        showSeriesLoadingAnimation();
        break;
    }
    case Message::controller_startDirectoryLoading_view:
    {
        progressIndicatorPath->startAnimation();
        break;
    }
    case Message::controller_stopDirectoryLoading_view:
    {
        progressIndicatorPath->stopAnimation();
        break;
    }
    case Message::controller_addNameScheme_view:
    {
        QString nameScheme = *msg.data[0].qsPointer;
        addNameSchemeItem(nameScheme);
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
    case Message::controller_removeNameScheme_view:
    {
        int indexToRemove = msg.data[0].i;
        removeNameSchemeItem(indexToRemove);
        break;
    }
    case Message::controller_replaceNameScheme_view:
    {
        int indexToChange = msg.data[0].i;
        QString newNameScheme = *msg.data[1].qsPointer;
        QString newNameSchemeEntry = QString::number(indexToChange + 1) + ": " + newNameScheme;
        ui->nameSchemeComboBox->setItemText(indexToChange, newNameSchemeEntry);
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
        setSeriesAvailableStatus(true, false);
        break;
    }
    case Message::controller_failureSeriesLoading_view:
    {
        setSeriesAvailableStatus(false, false);
        break;
    }
    case Message::controller_renameStarted_view:
    {
        disableGUIControl();
        showRenameProgress();
        break;
    }
    case Message::controller_updateRenameProgess_view:
    {
        int amountFiles = msg.data[0].i;
        int currentFile = msg.data[1].i;
        QString oldFileName = *msg.data[2].qsPointer;
        QString newFileName = *msg.data[3].qsPointer;
        Q_UNUSED(newFileName); // Not displayed currently, maybe later?
        updateRenameProgress(amountFiles, currentFile, oldFileName);
        break;
    }
    case Message::controller_renameFinished_view:
    {
        hideRenameProgress();
        enableGUIControl();
        break;
    }
    case Message::controller_enableUndoRenaming_view:
    {
        bool enableUndoRenaming = msg.data[0].b;
        undoRenameAction->setEnabled(enableUndoRenaming);
        break;
    }
    case Message::controller_seasonMismatch_view:
    {
        renameConfirmationMessageBox->show();
        renameConfirmationMessageBox->buttons().at(1)->setFocus();
        if (renameConfirmationMessageBox->exec() == 0) // 0 = Yes button
        {
            Message msgForceRename;
            msgForceRename.type = Message::view_forceRename_controller;
            emit(sendMessage(msgForceRename));
        } else
        {
            enableGUIControl();
        }
        ui->renameButton->setDown(false);
        break;
    }
    case Message::controller_setStatus_view:
    {
        QString status = *msg.data[0].qsPointer;
        int type = msg.data[1].i;
        setStatusMessage(status, type);
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
    case Message::controller_updateDirectoryWidget_view:
    {
        std::vector<QStringList> pathStructure = *msg.data[0].qsListVectorPointer;
        bool containsRoot = msg.data[1].b;
        QString path = *msg.data[2].qsPointer;

        updateDirectoryWidget(pathStructure, containsRoot, path);
        break;
    }
    case Message::controller_useDarkTheme_view:
    {
        changeToDarkTheme();
        // Workaround for white table headers
        updateRow(0, "", "", true);
        clearTable();
        break;
    }
    case Message::controller_setWindowRect_view:
    {
        QRect windowRect = *msg.data[0].qRectPointer;
        if (windowRect.y() >= 0)
        {
            this->setGeometry(windowRect);
        }
        break;
    }
    case Message::controller_showSeriesInfo_view:
    {
        seriesInformationEnabled = msg.data[0].b;
        ui->additionalInfoScrollArea->setVisible(seriesInformationEnabled);
        resizeEvent(NULL);
        break;
    }
    case Message::controller_setSeriesInfo_view:
    {
        QByteArray *imageByteArray = msg.data[0].qbPointer;
        QString totalEpisodes = *msg.data[1].qsPointer;
        QString season = *msg.data[2].qsPointer;
        QString totalSeasons = *msg.data[3].qsPointer;
        QString seriesName = *msg.data[4].qsPointer;
        QString airDate = *msg.data[5].qsPointer;
        QString plot = *msg.data[6].qsPointer;
        // Todo: integrate plot

        if (imageByteArray != NULL)
            seriesImage.loadFromData(*imageByteArray);
        else
            seriesImage.load(":/images/default_poster.jpg");
        ui->posterInfoLabel->setPixmap(seriesImage.scaled(ui->posterInfoLabel->width(), ui->posterInfoLabel->height(), Qt::KeepAspectRatio));

        ui->totalEpisodesInfoLabelData->setText(totalEpisodes);
        ui->seasonInfoLabelData->setText(season);
        ui->totalSeasonInfoLabelData->setText(totalSeasons);
        ui->seriesNameInfoLabelData->setText(seriesName);
        ui->airDateInfoLabelData->setText(airDate);

        resizeEvent(NULL);
        break;
    }
    case Message::controller_posterAlreadyExists_view:
    {
        posterConfirmationMessageBox->show();
        posterConfirmationMessageBox->buttons().at(1)->setFocus();
        if (posterConfirmationMessageBox->exec() == 0) // 0 = Yes button
        {
            Message msgForceSavePoster;
            msgForceSavePoster.type = Message::view_forceSavePoster_conroller;
            emit(sendMessage(msgForceSavePoster));
        }
        break;
    }
    default:
        break;
    }
}

bool MainWindow::updateRow(int row, QString oldFileName, QString newFileName, bool noColorization)
{
    // Check if trying to access rows, that are not existent and not the next possible new row
    if (row > ui->episodeNameTable->rowCount())
        return false;
    else
        ui->episodeNameTable->setStyleSheet(whiteBackground);

    // Check if row items already exist to prevent multiple creations
    if (ui->episodeNameTable->item(row, 0) != NULL && ui->episodeNameTable->item(row, 1) != NULL)
    {
        ui->episodeNameTable->item(row, 0)->setText(oldFileName);
        ui->episodeNameTable->item(row, 1)->setText(newFileName);
    }
    else // Not existing
    {
        QTableWidgetItem *oldFile = new QTableWidgetItem(oldFileName);
        QTableWidgetItem *newFile = new QTableWidgetItem(newFileName);
        oldFile->setFlags(oldFile->flags() & ~Qt::ItemIsEditable);

        ui->episodeNameTable->insertRow(row);
        ui->episodeNameTable->setItem(row, 0, oldFile);
        ui->episodeNameTable->setItem(row, 1, newFile);
    }

    QColor greyedOut = QColor(100, 100, 100);
    QColor black = QColor(0, 0, 0);
    // Colorize the table item
    if (oldFileName.isEmpty() && !newFileName.isEmpty() && !noColorization)
    {
        ui->episodeNameTable->item(row, 1)->setTextColor(greyedOut);
    }
    else if (!oldFileName.isEmpty() && newFileName.isEmpty() && !noColorization)
    {
        ui->episodeNameTable->item(row, 0)->setTextColor(greyedOut);
    }
    else if (oldFileName == newFileName)
    {
        ui->episodeNameTable->item(row, 0)->setTextColor(greyedOut);
        ui->episodeNameTable->item(row, 1)->setTextColor(greyedOut);
    }
    else
    {
        ui->episodeNameTable->item(row, 0)->setTextColor(black);
        ui->episodeNameTable->item(row, 1)->setTextColor(black);
    }
    return true;
}
