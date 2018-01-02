#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QDesktopServices>
#include <QDebug>

#include "languagedata.h"
#include "seriesparser.h"

#define UNIVERSAL_SPACER 10
#define GROUPBOX_HEIGHT 70
#define MINIMUM_WINDOW_WIDTH 1050
#define MINIMUM_WINDOW_HEIGHT 620
#define MINIMUM_PATH_STRUCTURE_BOX_SIZE 150

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    chosenPath(QDir::homePath())
{
    ui->setupUi(this);
    seriesTextChangeTimer = new QTimer(this);
    clearStatusTextTimer = new QTimer(this);
    hideRenameProgressTimer = new QTimer(this);
    statusBarTypeImageLabel = new QLabel();
    renameShadow = new CustomShadowEffect(ui->renameProgressScrollArea);
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
    msgSetWindowRect.type = Message::Type::view_setWindowRect_controller;
    msgSetWindowRect.data[0].qRectPointer = &windowRect;
    emit(sendMessage(msgSetWindowRect));

    Message msgSetDirectorySelector;
    msgSetDirectorySelector.type = Message::Type::view_setDirectorySelector_controller;
    msgSetDirectorySelector.data[0].i = (int)directorySelector;
    emit(sendMessage(msgSetDirectorySelector));

    delete ui;
    delete seriesTextChangeTimer;
    delete clearStatusTextTimer;
    delete hideRenameProgressTimer;
    delete statusBarTypeImageLabel;
    delete renameShadow;
    delete renameSlideProgressAnimation;
    delete renameConfirmationMessageBox;
    delete posterConfirmationMessageBox;
    delete fileMenu;
    delete helpMenu;
    delete directoryEntriesMenu;
    delete directoryMenu;
    delete savePosterAction;
    delete undoRenameAction;
    delete openDirectoryAction;
    delete switchDirectorySelectorAction;
    delete reloadDirectoryAction;
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
    ui->centralControlElementWidget->setFixedHeight(90);

    ui->seriesInfohorizontalLayout->setStretch(0, 3);
    ui->seriesInfohorizontalLayout->setStretch(1, 1);
    ui->seriesSelectionHorizontalLayout->setStretch(0, 8);
    ui->seriesSelectionHorizontalLayout->setStretch(1, 2);
    ui->seriesSelectionHorizontalLayout->setStretch(2, 3);
    ui->seriesSelectionHorizontalLayout->setStretch(3, 4);

    ui->additionalInfoScrollArea->setLayout(ui->additionalScrollAreaHorizontalLayout);
    ui->plotGroupBox->setLayout(ui->plotTextVerticalLayout);
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
    openDirectoryAction->setIcon(QIcon(":/images/folder.png"));
    switchDirectorySelectorAction->setIcon(QIcon(":/images/notepad.png"));
    reloadDirectoryAction->setIcon(QIcon(":/images/update.png"));
    fullScreenAction->setIcon(QIcon(":/images/fullscreen.png"));

    // Initialize view state
    ui->renameButton->setEnabled(false);
    savePosterAction->setEnabled(false);
    undoRenameAction->setEnabled(false);
    ui->seasonComboBox->setEnabled(false);
    ui->additionalInfoScrollArea->hide();
    ui->correctSeriesLabel->hide();

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
    directoryMenu = new QMenu("Directory");
    viewMenu = new QMenu("Display");
    helpMenu = new QMenu("Help");

    savePosterAction = new QAction("Save poster");
    undoRenameAction = new QAction("Undo renaming");

    openDirectoryAction = new QAction("Selection");
    switchDirectorySelectorAction = new QAction("Switch directory view");
    reloadDirectoryAction = new QAction("Reload");

    aboutAction = new QAction(aboutText);
    settingsAction = new QAction("Settings");
    fullScreenAction = new QAction("Fullscreen");

    aboutAction->setMenuRole(QAction::ApplicationSpecificRole);
    settingsAction->setMenuRole(QAction::ApplicationSpecificRole);

    savePosterAction->setShortcut(QKeySequence::Save);
    undoRenameAction->setShortcut(QKeySequence::Undo);
    settingsAction->setShortcut(QKeySequence::Preferences);
    openDirectoryAction->setShortcut(QKeySequence::Open);
    switchDirectorySelectorAction->setShortcut(QKeySequence::AddTab);
    reloadDirectoryAction->setShortcut(QKeySequence::Refresh);
    fullScreenAction->setShortcut(QKeySequence::FullScreen);

    fileMenu->addAction(savePosterAction);
    fileMenu->addSeparator();
    fileMenu->addAction(undoRenameAction);
    fileMenu->addAction(settingsAction);
    directoryMenu->addAction(openDirectoryAction);
    directoryMenu->addAction(switchDirectorySelectorAction);
    directoryMenu->addAction(reloadDirectoryAction);
    helpMenu->addAction(aboutAction);
    viewMenu->addAction(fullScreenAction);

    ui->menuBar->addMenu(fileMenu);
    ui->menuBar->addMenu(directoryMenu);
    ui->menuBar->addMenu(viewMenu);
    ui->menuBar->addMenu(helpMenu);

    // Connect Actions
    QObject::connect(savePosterAction, SIGNAL(triggered(bool)), this, SLOT(savePoster()));
    QObject::connect(undoRenameAction, SIGNAL(triggered(bool)), this, SLOT(undoRenaming()));
    QObject::connect(openDirectoryAction, SIGNAL(triggered(bool)), this, SLOT(openDirectory()));
    QObject::connect(switchDirectorySelectorAction, SIGNAL(triggered(bool)), this, SLOT(toggleDirectorySelector()));
    QObject::connect(reloadDirectoryAction, SIGNAL(triggered(bool)), this, SLOT(onUpdateDirectory()));
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
    ui->directPathInputLineEdit->hide();

    ui->directoryWidgetHorizontalLayout->addWidget(progressIndicatorPath);
    directoryEntriesMenu = new QMenu(this);

    QObject::connect(ui->directPathInputLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onPathLineEditTextChanged(QString)));
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

    renameShadow->setBlurRadius(40.0);
    renameShadow->setDistance(6.0);
    renameShadow->setColor(QColor(0, 0, 0, 150));

    renameSlideProgressAnimation = new QPropertyAnimation(ui->renameProgressScrollArea, "geometry");
    renameSlideProgressAnimation->setDuration(150);

    ui->renameProgressScrollArea->hide();
    ui->renameProgressScrollArea->setGraphicsEffect(renameShadow);
}

void MainWindow::setSeriesAvailableStatus(bool status, bool isEmpty)
{
    if (isEmpty)
    {
        ui->seriesLineEdit->setStyleSheet(colorWhite);
        ui->correctSeriesLabel->hide();
        progressIndicatorSeries->show();
        progressIndicatorSeries->stopAnimation();
    }
    else if (status)
    {
        ui->seriesLineEdit->setStyleSheet(colorGreen);
        ui->correctSeriesLabel->setPixmap(QPixmap(":/images/check-20.png"));
        hideSeriesLoadingAnimation();
    }
    else
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
        episodeTableWidth = 0.80 * (windowWidth - 2 * UNIVERSAL_SPACER);
        renameProgressWidgetX = (episodeTableWidth - renameProgressWidgetWidth) / 2;
        int additionalInfoWidth = 0.20 * (windowWidth - 2 * UNIVERSAL_SPACER);
        int additionalInfoHeight = episodeTableHeight;

        if (additionalInfoWidth > 300)
        {
            additionalInfoWidth = 300;
            episodeTableWidth = windowWidth - 2 * UNIVERSAL_SPACER - additionalInfoWidth;
        }
        int imageLabelWidth = additionalInfoWidth - 2 * UNIVERSAL_SPACER;
        int imageLabelHeight = episodeTableHeight * 0.6;
        int additionalInfoX = episodeTableX + episodeTableWidth - 1;
        int additionalInfoY = UNIVERSAL_SPACER;

        // Scale before further movements to make sure we have the correct image size
        ui->posterInfoLabel->setPixmap(seriesImage.scaled(imageLabelWidth, imageLabelHeight, Qt::KeepAspectRatio));
        ui->posterInfoLabel->setFixedSize(ui->posterInfoLabel->pixmap()->size());
        // Resize
        ui->additionalInfoScrollArea->setFixedSize(additionalInfoWidth, additionalInfoHeight);
        // Move
        ui->additionalInfoScrollArea->move(additionalInfoX, additionalInfoY);
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

void MainWindow::updateView(EpisodeNames* episodeNames, bool atLeastOneSideEmpty, int amountSeasons)
{
    // Avoid firing cell changed signals
    QObject::disconnect(ui->episodeNameTable, SIGNAL(cellChanged(int,int)), this, SLOT(onTableEntryChanged(int,int)));

    const auto tableSize = episodeNames->size();
    setAmountSeasons(amountSeasons);
    ui->episodeNameTable->setRowCount(tableSize);

    // Fill table
    for (size_t row = 0; row < tableSize; row++)
    {
        updateRow(row, episodeNames->at(row), atLeastOneSideEmpty);
    }

    QObject::connect(ui->episodeNameTable, SIGNAL(cellChanged(int,int)), this, SLOT(onTableEntryChanged(int,int)));
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
    if (DirectorySelector::text == directorySelector)
    {
        return;
    }

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
    colorWhite = "QLineEdit { background: rgb(25, 25, 25); }";
    colorGreen = "QLineEdit { background: rgb(4, 55, 4); }";
    colorRed = "QLineEdit { background: rgb(55, 15, 15); }";
    imageBackground = QString("background-image: url(:/images/logo.png); ")
            + QString("background-color: rgb(30, 30, 30);")
            + QString("background-repeat: no-repeat; ")
            + QString("background-attachment: fixed; ")
            + QString("background-position: center;");
    renameShadow->setColor(QColor(255, 255, 255, 150));
    greyedOutColor = QColor(155, 155, 155);
    normalColor = QColor(255, 255, 255);
    lightRedColor = QColor(96, 31, 31);
    whiteColor = QColor(25, 25, 25);

    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    if (ui->episodeNameTable->itemAt(1,1) == nullptr)
    {
        clearTable();
    }
    // Workaround for white table headers
    EpisodeName episodeName{};
    updateRow(0, episodeName, true);
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
    while (currentFileTextWidth >= ui->renameProgressScrollArea->width()
           - ui->renamingProgressFileOutputLabel->width() - 4 * UNIVERSAL_SPACER - 5)
    {
        oldFileName.chop(2);
        currentFileTextWidth = fm.width(oldFileName);
        chopedOff = true;
    }
    if (chopedOff)
        oldFileName += "...";
    ui->renamingProgressCurrentFileLabel->setText(oldFileName);
}

void MainWindow::switchDirectorySelector(MainWindow::DirectorySelector directorySelector)
{
    this->directorySelector = directorySelector;

    switch (directorySelector)
    {
    case DirectorySelector::text:
        ui->pathStructure1ComboBox->hide();
        ui->pathStructure2ComboBox->hide();
        ui->pathStructure3ComboBox->hide();
        ui->pathStructure4ComboBox->hide();
        ui->pathStructureContentButton->hide();

        ui->directPathInputLineEdit->show();
        QObject::connect(ui->directPathInputLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onPathLineEditTextChanged(QString)));
        break;

    case DirectorySelector::widget:
    default:
        ui->directPathInputLineEdit->hide();
        QObject::disconnect(ui->directPathInputLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onPathLineEditTextChanged(QString)));

        ui->pathStructure1ComboBox->show();
        ui->pathStructure2ComboBox->show();
        ui->pathStructureContentButton->show();
        updateDirectoryWidgetVisibility();

        break;
    }
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

void MainWindow::setStatusMessage(QString message, StatusMessageType type)
{
    clearStatusTextTimer->stop();
    QString labelText;
    switch (type)
    {
    case StatusMessageType::error:
    {
        labelText = "<img src=:/images/error.png> ";
        break;
    }
    case StatusMessageType::success:
    {
        labelText = "<img src=:/images/check.png> ";
        break;
    }
    case StatusMessageType::info:
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
    tableHeader << translationList.at((int)LanguageData::Translate::oldName)
                << translationList.at((int)LanguageData::Translate::newName);

    ui->episodeNameTable->setHorizontalHeaderLabels(tableHeader);
    ui->pathGroupBox->setTitle(translationList.at((int)LanguageData::Translate::directorySelection));
    ui->selectionButton->setText(translationList.at((int)LanguageData::Translate::selection));
    ui->pathLabel->setText(translationList.at((int)LanguageData::Translate::path));
    ui->seriesGroupBox->setTitle(translationList.at((int)LanguageData::Translate::seriesSelection));
    ui->seriesLabel->setText(translationList.at((int)LanguageData::Translate::series));
    ui->seasonLabel->setText(translationList.at((int)LanguageData::Translate::season));
    ui->seriesLanguageLabel->setText(translationList.at((int)LanguageData::Translate::language));
    ui->nameSchemeLabel->setText(translationList.at((int)LanguageData::Translate::nameScheme));
    ui->renameButton->setText(translationList.at((int)LanguageData::Translate::rename));
    // Menubar
    fileMenu->setTitle(translationList.at((int)LanguageData::Translate::file));
    viewMenu->setTitle(translationList.at((int)LanguageData::Translate::display));
    helpMenu->setTitle(translationList.at((int)LanguageData::Translate::help));
    directoryMenu->setTitle(translationList.at((int)LanguageData::Translate::directory));
    aboutAction->setText(translationList.at((int)LanguageData::Translate::about) + " " + APPLICATIONNAME);
    settingsAction->setText(translationList.at((int)LanguageData::Translate::settings));
    savePosterAction->setText(translationList.at((int)LanguageData::Translate::savePoster));
    undoRenameAction->setText(translationList.at((int)LanguageData::Translate::undoRenaming));
    fullScreenAction->setText(translationList.at((int)LanguageData::Translate::fullscreen));
    openDirectoryAction->setText(translationList.at((int)LanguageData::Translate::selection));
    switchDirectorySelectorAction->setText(translationList.at((int)LanguageData::Translate::switchDirectoryView));
    reloadDirectoryAction->setText(translationList.at((int)LanguageData::Translate::reload));
    // Info sidebar
    ui->infoGroupBox->setTitle(translationList.at((int)LanguageData::Translate::seriesInfo));
    ui->airDateInfoLabel->setText(translationList.at((int)LanguageData::Translate::airDate) + ":");
    ui->seasonInfoLabel->setText(translationList.at((int)LanguageData::Translate::season) + ":");
    ui->totalEpisodesInfoLabel->setText(translationList.at((int)LanguageData::Translate::episodeNumber) + ":");
    // Rename confirmation dialog
    renameConfirmationMessageBox->setWindowTitle(translationList.at((int)LanguageData::Translate::areYouSure));
    renameConfirmationMessageBox->setText(translationList.at((int)LanguageData::Translate::forceRename));
    renameConfirmationMessageBox->setButtonText(0, translationList.at((int)LanguageData::Translate::yes));
    renameConfirmationMessageBox->setButtonText(1, translationList.at((int)LanguageData::Translate::no));
    // Poster confirmation dialog
    posterConfirmationMessageBox->setWindowTitle(translationList.at((int)LanguageData::Translate::overridePoster));
    posterConfirmationMessageBox->setText(translationList.at((int)LanguageData::Translate::posterAlreadyExists));
    posterConfirmationMessageBox->setButtonText(0, translationList.at((int)LanguageData::Translate::yes));
    posterConfirmationMessageBox->setButtonText(1, translationList.at((int)LanguageData::Translate::no));
    // Undo renaming confirmation dialog
    undoRenameConfirmationBox->setWindowTitle(translationList.at((int)LanguageData::Translate::undoRenaming));
    undoRenameConfirmationBox->setText(translationList.at((int)LanguageData::Translate::undoRenamingDetailed));
    undoRenameConfirmationBox->setButtonText(0, translationList.at((int)LanguageData::Translate::yes));
    undoRenameConfirmationBox->setButtonText(1, translationList.at((int)LanguageData::Translate::no));
    // Renaming progress widget
    ui->renamingLabel->setText(translationList.at((int)LanguageData::Translate::renaming) + ":");
    ui->renamingProgressFileOutputLabel->setText(translationList.at((int)LanguageData::Translate::file) + ":");
    // Misc
    directorySelectionText = translationList.at((int)LanguageData::Translate::directorySelection);
    openThisFolderText = translationList.at((int)LanguageData::Translate::openThisFolder);
    if (directoryEntriesMenu->actions().size() > 0)
    {
        directoryEntriesMenu->actions().last()->setText(openThisFolderText);
    }
}

void MainWindow::openDirectory()
{
    // Open directory-dialog to chose directory
    QString directoryPath =
            QFileDialog::getExistingDirectory(this, directorySelectionText, chosenPath.path());
    QDir dir(directoryPath);

    if (!directoryPath.isNull() && dir.exists())
    {
        chosenPath = directoryPath;
        ui->directoryUpdateButton->setEnabled(true);

        Message directoryChangedMsg;
        directoryChangedMsg.type = Message::Type::view_changeDirectory_controller;
        directoryChangedMsg.data[0].qsPointer = &directoryPath;
        emit(sendMessage(directoryChangedMsg));
    }
}


void MainWindow::onUpdateDirectory()
{
    Message directoryUpdateMsg;
    directoryUpdateMsg.type = Message::Type::view_updateDirectory_controller;
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
    msg.type = Message::Type::view_changeSeriesText_controller;
    msg.data[0].qsPointer = &seriesText;
    msg.data[1].i = 1;
    emit(sendMessage(msg));
}

void MainWindow::onSeasonChanged(int index)
{
    Message seasonChangedMsg;
    seasonChangedMsg.type = Message::Type::view_changeSeason_controller;
    seasonChangedMsg.data[0].i = index + 1;
    emit(sendMessage(seasonChangedMsg));
}

void MainWindow::onRenameButtonPressed()
{
    Message renameMsg;
    renameMsg.type = Message::Type::view_rename_controller;
    emit(sendMessage(renameMsg));
}

void MainWindow::onNameSchemeChanged(int index)
{
    Message msgNameSchemeChanged;
    msgNameSchemeChanged.type = Message::Type::view_changeNameScheme_controller;
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
        msgChangeNewFileName.type = Message::Type::view_changeNewFileName_controller;
        msgChangeNewFileName.data[0].i = row;
        msgChangeNewFileName.data[1].qsPointer = &newFileName;
        emit(sendMessage(msgChangeNewFileName));
    }
}

void MainWindow::onPathLineEditTextChanged(QString path)
{
    Message directoryChangedMsg;
    directoryChangedMsg.type = Message::Type::view_changeDirectory_controller;
    directoryChangedMsg.data[0].qsPointer = &path;
    emit(sendMessage(directoryChangedMsg));
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
    msgSwitchToFolder.type = Message::Type::view_switchToDirectory_controller;
    msgSwitchToFolder.data[0].i = level;
    msgSwitchToFolder.data[1].i = selection;
    emit(sendMessage(msgSwitchToFolder));
}

void MainWindow::toggleDirectorySelector()
{
    if (DirectorySelector::text == directorySelector)
    {
        switchDirectorySelector(DirectorySelector::widget);
    }
    else
    {
        switchDirectorySelector(DirectorySelector::text);
    }
}

void MainWindow::clearStatusText()
{
    clearStatusTextTimer->stop();
    statusBarTypeImageLabel->clear();
}

void MainWindow::savePoster()
{
    Message msgSavePoster;
    msgSavePoster.type = Message::Type::view_savePoster_controller;
    emit(sendMessage(msgSavePoster));
}

void MainWindow::undoRenaming()
{
    undoRenameConfirmationBox->show();
    undoRenameConfirmationBox->buttons().at(1)->setFocus();
    if (undoRenameConfirmationBox->exec() == 0) // 0 = Yes button
    {
        Message msgUndoRenaming;
        msgUndoRenaming.type = Message::Type::view_undoRenaming_controller;
        emit(sendMessage(msgUndoRenaming));
    }
}

void MainWindow::showAboutDialog()
{
    Message msgShowAbout;
    msgShowAbout.type = Message::Type::view_showAboutDialog_controller;
    emit(sendMessage(msgShowAbout));
}

void MainWindow::showSettingsWindow()
{
    Message msgShowSettings;
    msgShowSettings.type = Message::Type::view_showSettingsWindow_controller;
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
    msgChangeSeriesLanguage.type = Message::Type::view_changeSeriesLanguage_controller;
    msgChangeSeriesLanguage.data[0].i = index;
    emit(sendMessage(msgChangeSeriesLanguage));
}

void MainWindow::notify(Message &msg)
{
    switch (msg.type) {
    case Message::Type::controller_updateView_view:
    {
        int amountSeasons = msg.data[0].i;
        EpisodeNames* episodeNames = msg.data[1].episodeNamesPointer;
        bool atLeastOneSideEmpty = msg.data[2].b;

        updateView(episodeNames, atLeastOneSideEmpty, amountSeasons);
        break;
    }
    case Message::Type::controller_seriesSet_view:
    {
        bool seriesSet = msg.data[0].b;
        bool isEmpty = msg.data[1].b;
        setSeriesAvailableStatus(seriesSet, isEmpty);
        break;
    }
    case Message::Type::controller_enableRenameButton_view:
    {
        bool enableButton = msg.data[0].b;
        ui->renameButton->setEnabled(enableButton);
        break;
    }
    case Message::Type::controller_enableSavePoster_view:
    {
        bool savePoster = msg.data[0].b;
        savePosterAction->setEnabled(savePoster);
        break;
    }
    case Message::Type::controller_startSeriesLoading_view:
    {
        showSeriesLoadingAnimation();
        break;
    }
    case Message::Type::controller_startDirectoryLoading_view:
    {
        progressIndicatorPath->startAnimation();
        break;
    }
    case Message::Type::controller_stopDirectoryLoading_view:
    {
        progressIndicatorPath->stopAnimation();
        break;
    }
    case Message::Type::controller_switchDirectorySelector_view:
    {
        auto selectedDirectorySelector = (DirectorySelector)msg.data[0].i;
        switchDirectorySelector(selectedDirectorySelector);
        break;
    }
    case Message::Type::controller_addNameScheme_view:
    {
        QString nameScheme = *msg.data[0].qsPointer;
        addNameSchemeItem(nameScheme);
        break;
    }
    case Message::Type::controller_addNameSchemes_view:
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
    case Message::Type::controller_removeNameScheme_view:
    {
        int indexToRemove = msg.data[0].i;
        removeNameSchemeItem(indexToRemove);
        break;
    }
    case Message::Type::controller_replaceNameScheme_view:
    {
        int indexToChange = msg.data[0].i;
        QString newNameScheme = *msg.data[1].qsPointer;
        QString newNameSchemeEntry = QString::number(indexToChange + 1) + ": " + newNameScheme;
        ui->nameSchemeComboBox->setItemText(indexToChange, newNameSchemeEntry);
        break;
    }
    case Message::Type::controller_changeLocalization_view:
    {
        QStringList translationList = *msg.data[0].qsListPointer;
        changeLocalization(translationList);
        break;
    }
    case Message::Type::controller_addSeriesLanguages_view:
    {
        QStringList seriesLanguageList = *msg.data[0].qsListPointer;
        for (int i = 0; i < seriesLanguageList.size(); i++)
            ui->seriesLanguageComboBox->addItem(seriesLanguageList.at(i));
        break;
    }
    case Message::Type::controller_successSeriesLoading_view:
    {
        setSeriesAvailableStatus(true, false);
        break;
    }
    case Message::Type::controller_failureSeriesLoading_view:
    {
        setSeriesAvailableStatus(false, false);
        break;
    }
    case Message::Type::controller_renameStarted_view:
    {
        disableGUIControl();
        showRenameProgress();
        break;
    }
    case Message::Type::controller_updateRenameProgess_view:
    {
        int amountFiles = msg.data[0].i;
        int currentFile = msg.data[1].i;
        QString oldFileName = *msg.data[2].qsPointer;
        QString newFileName = *msg.data[3].qsPointer;
        Q_UNUSED(newFileName); // Not displayed currently, maybe later?
        updateRenameProgress(amountFiles, currentFile, oldFileName);
        break;
    }
    case Message::Type::controller_renameFinished_view:
    {
        hideRenameProgress();
        enableGUIControl();
        break;
    }
    case Message::Type::controller_enableUndoRenaming_view:
    {
        bool enableUndoRenaming = msg.data[0].b;
        undoRenameAction->setEnabled(enableUndoRenaming);
        break;
    }
    case Message::Type::controller_seasonMismatch_view:
    {
        renameConfirmationMessageBox->show();
        renameConfirmationMessageBox->buttons().at(1)->setFocus();
        if (renameConfirmationMessageBox->exec() == 0) // 0 = Yes button
        {
            Message msgForceRename;
            msgForceRename.type = Message::Type::view_forceRename_controller;
            emit(sendMessage(msgForceRename));
        } else
        {
            enableGUIControl();
        }
        ui->renameButton->setDown(false);
        break;
    }
    case Message::Type::controller_setStatus_view:
    {
        QString status = *msg.data[0].qsPointer;
        int type = msg.data[1].i;
        setStatusMessage(status, (StatusMessageType)type);
        break;
    }
    case Message::Type::controller_changeSeriesParser_view:
    {
        int selectedSeriesParser = msg.data[0].i;
        switch ((SeriesParser::Parser)selectedSeriesParser)
        {
        default:
        case SeriesParser::Parser::tmdb:
        {
            ui->seriesLanguageComboBox->setEnabled(true);
            break;
        }
        case SeriesParser::Parser::omdb:
        {
            ui->seriesLanguageComboBox->setEnabled(false);
            break;
        }
        }
        break;
    }
    case Message::Type::controller_changeSeriesLanguage_view:
    {
        QString language = *msg.data[0].qsPointer;
        int indexOfLanguage = ui->seriesLanguageComboBox->findText(language);
        ui->seriesLanguageComboBox->setCurrentIndex(indexOfLanguage);
        break;
    }
    case Message::Type::controller_changeNameScheme_view:
    {
        int nameSchemeIndex = msg.data[0].i;
        ui->nameSchemeComboBox->setCurrentIndex(nameSchemeIndex);
        break;
    }
    case Message::Type::controller_setSeries_view:
    {
        QString series = *msg.data[0].qsPointer;
        int season = msg.data[1].i - 1;
        ui->seriesLineEdit->setText(series);
        ui->seasonComboBox->setCurrentIndex(season);
        seriesTextChangeTimer->stop(); // Avoid double loading
        break;
    }
    case Message::Type::controller_setSeason_view:
    {
        int season = msg.data[0].i - 1;
        ui->seasonComboBox->setCurrentIndex(season);
        seriesTextChangeTimer->stop(); // Avoid double loading
        break;
    }
    case Message::Type::controller_setPath_view:
    {
        const QString path = *msg.data[0].qsPointer;
        ui->directPathInputLineEdit->setText(path);
        break;
    }
    case Message::Type::controller_directorySetSuccessful_view:
    {
        const auto setSuccessful = msg.data[0].b;
        const auto isEmpty = msg.data[1].b;
        // Todo: Add status / loading icon
        if (isEmpty)
        {
            ui->directPathInputLineEdit->setStyleSheet(colorWhite);
        }
        else if (setSuccessful)
        {
            ui->directPathInputLineEdit->setStyleSheet(colorGreen);
        }
        else
        {
            ui->directPathInputLineEdit->setStyleSheet(colorRed);
        }
        break;
    }
    case Message::Type::controller_updateDirectoryWidget_view:
    {
        std::vector<QStringList> pathStructure = *msg.data[0].qsListVectorPointer;
        bool containsRoot = msg.data[1].b;
        QString path = *msg.data[2].qsPointer;

        updateDirectoryWidget(pathStructure, containsRoot, path);
        break;
    }
    case Message::Type::controller_useDarkTheme_view:
    {
        changeToDarkTheme();
        break;
    }
    case Message::Type::controller_setWindowRect_view:
    {
        QRect windowRect = *msg.data[0].qRectPointer;
        if (windowRect.y() >= 0)
        {
            this->setGeometry(windowRect);
        }
        break;
    }
    case Message::Type::controller_showSeriesInfo_view:
    {
        seriesInformationEnabled = msg.data[0].b;
        ui->additionalInfoScrollArea->setVisible(seriesInformationEnabled);
        resizeEvent(nullptr);
        break;
    }
    case Message::Type::controller_setSeriesInfo_view:
    {
        QByteArray *imageByteArray = msg.data[0].qbPointer;
        QString totalEpisodes = *msg.data[1].qsPointer;
        QString season = *msg.data[2].qsPointer;
        QString totalSeasons = *msg.data[3].qsPointer;
        QString seriesName = *msg.data[4].qsPointer;
        QString airDate = *msg.data[5].qsPointer;
        QString plot = *msg.data[6].qsPointer;

        if (imageByteArray != nullptr)
        {
            seriesImage.loadFromData(*imageByteArray);
        }
        else
        {
            seriesImage.load(":/images/default_poster.jpg");
        }
        ui->plotPlainTextEdit->clear();
        ui->plotPlainTextEdit->appendPlainText(plot);
        ui->plotPlainTextEdit->moveCursor(QTextCursor::Start);
        ui->posterInfoLabel->setPixmap(seriesImage.scaled(ui->posterInfoLabel->width(), ui->posterInfoLabel->height(), Qt::KeepAspectRatio));

        ui->totalEpisodesInfoLabelData->setText(totalEpisodes);
        ui->seasonInfoLabelData->setText(season);
        ui->totalSeasonInfoLabelData->setText(totalSeasons);
        ui->seriesNameInfoLabelData->setText(seriesName);
        ui->airDateInfoLabelData->setText(airDate);

        resizeEvent(nullptr);
        break;
    }
    case Message::Type::controller_posterAlreadyExists_view:
    {
        posterConfirmationMessageBox->show();
        posterConfirmationMessageBox->buttons().at(1)->setFocus();
        if (posterConfirmationMessageBox->exec() == 0) // 0 = Yes button
        {
            Message msgForceSavePoster;
            msgForceSavePoster.type = Message::Type::view_forceSavePoster_conroller;
            emit(sendMessage(msgForceSavePoster));
        }
        break;
    }
    default:
        break;
    }
}

void MainWindow::updateRow(int row, EpisodeName& episodeName, bool noColorization)
{
    const auto oldFileName = episodeName.getOldName();
    const auto newFileName = episodeName.getNewName();

    const auto& table = ui->episodeNameTable;
    auto leftSide = table->item(row, 0);
    auto rightSide = table->item(row, 1);
    const auto tableSize = table->rowCount();

    if (row > tableSize)
    {
        const auto error =
                QString("MainWindow::updateRow(): Trying to access invalid row at ")
                + QString::number(row)
                + QString(", but table size is ")
                + QString::number(tableSize);
        throw std::runtime_error(error.toStdString().c_str());
    }

    // Insert both text fields if they are not already set.
    if (leftSide == nullptr || rightSide == nullptr)
    {
        leftSide = new QTableWidgetItem();
        rightSide = new QTableWidgetItem();

        leftSide->setFlags(leftSide->flags() & ~Qt::ItemIsEditable);

        table->setItem(row, 0, leftSide);
        table->setItem(row, 1, rightSide);
    }

    leftSide->setText(oldFileName);
    rightSide->setText(newFileName);

    table->setStyleSheet(whiteBackground);
    leftSide->setTextColor(normalColor);
    rightSide->setTextColor(normalColor);

    // Red background if position is not determined.
    if (!episodeName.isPositionDetermined() && !oldFileName.isEmpty())
    {
        leftSide->setBackground(QBrush(lightRedColor));
    }
    else
    {
        leftSide->setBackground(whiteColor);
    }

    if (noColorization)
    {
        return;
    }

    // Grey out what will not be renamed.
    if (episodeName.atLeastOneNameEmpty())
    {
        if (oldFileName.isEmpty())
        {
            rightSide->setTextColor(greyedOutColor);
        }
        else if (newFileName.isEmpty())
        {
            leftSide->setTextColor(greyedOutColor);
        }
    }
    else if (episodeName.newAndOldAreEqual())
    {
        leftSide->setTextColor(greyedOutColor);
        rightSide->setTextColor(greyedOutColor);
    }
}
