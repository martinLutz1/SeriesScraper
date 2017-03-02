#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "languagedata.h"
#include "seriesparser.h"
#include <QDebug>

#define UNIVERSAL_SPACER 10

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    createResetConfirmationDialog();;
    windowSize = this->size();

    keyPressEaterEscapeSettings = new KeyPressEater;
    keyPressEaterDeleteNameScheme = new KeyPressEater;
    keyPressEaterDeleteFileType = new KeyPressEater;
    keyPressEaterEnterNameScheme = new KeyPressEater;
    keyPressEaterEnterFileType = new KeyPressEater;

    keyPressEaterEscapeSettings->setKey(Qt::Key_Escape);
    keyPressEaterDeleteNameScheme->setKey(Qt::Key_Delete);
    keyPressEaterDeleteFileType->setKey(Qt::Key_Delete);
#if defined (Q_OS_MACX)
    keyPressEaterDeleteNameScheme->setKey(Qt::Key_Backspace);
    keyPressEaterDeleteFileType->setKey(Qt::Key_Backspace);
#endif
    keyPressEaterEnterNameScheme->setKey(16777220); // Enter key
    keyPressEaterEnterFileType->setKey(16777220);

    this->installEventFilter(keyPressEaterEscapeSettings);
    ui->fileTypeListWidget->installEventFilter(keyPressEaterDeleteFileType);
    ui->newFileTypeLineEdit->installEventFilter(keyPressEaterEnterFileType);
    ui->nameSchemeListWidget->installEventFilter(keyPressEaterDeleteNameScheme);
    ui->newNameSchemeLineEdit->installEventFilter(keyPressEaterEnterNameScheme);

    ui->newNameSchemeAddButton->setEnabled(false);
    ui->nameSchemeRemoveButton->setEnabled(false);
    ui->newFileTypeAddButton->setEnabled(false);
    ui->fileTypeRemoveButton->setEnabled(false);

    QObject::connect(keyPressEaterEscapeSettings, SIGNAL(keyPressed()), this, SLOT(hide()));
    QObject::connect(ui->doneButton, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(ui->selectInterfaceLanguageComboBox, SIGNAL(activated(QString)), this, SLOT(onGUILanguageChanged(QString)));
    QObject::connect(ui->tmdbRadioButton, SIGNAL(clicked(bool)), this, SLOT(onSeriesParserChanged()));
    QObject::connect(ui->omdbRadioButton, SIGNAL(clicked(bool)), this, SLOT(onSeriesParserChanged()));
    QObject::connect(ui->tvdbRadioButton, SIGNAL(clicked(bool)), this, SLOT(onSeriesParserChanged()));
    QObject::connect(ui->saveSeriesCheckBox, SIGNAL(toggled(bool)), this, SLOT(onSaveSeriesChanged(bool)));
    QObject::connect(ui->savePathCheckBox, SIGNAL(toggled(bool)), this, SLOT(onSavePathChanged(bool)));
    QObject::connect(ui->savePosterCheckBox, SIGNAL(toggled(bool)), this, SLOT(onSavePosterChanged(bool)));
    QObject::connect(ui->autoSetDetectedSeasonCheckBox, SIGNAL(toggled(bool)), this, SLOT(onSetDetectedSeason(bool)));
    QObject::connect(ui->resetButton, SIGNAL(pressed()), this, SLOT(onResetClicked()));
    QObject::connect(ui->darkThemeCheckBox, SIGNAL(toggled(bool)), this, SLOT(onDarkThemeChanged(bool)));
    QObject::connect(ui->showSeriesInformationCheckBox, SIGNAL(toggled(bool)), this, SLOT(onShowSeriesInformationChanged(bool)));
    QObject::connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onTabChanged(int)));

    // Connections of file type section
    QObject::connect(ui->newFileTypeAddButton, SIGNAL(pressed()), this, SLOT(onAddFileType()));
    QObject::connect(keyPressEaterEnterFileType, SIGNAL(keyPressed()), this, SLOT(onAddFileType()));
    QObject::connect(ui->fileTypeRemoveButton, SIGNAL(pressed()), this, SLOT(onRemoveFileType()));
    QObject::connect(keyPressEaterDeleteFileType, SIGNAL(keyPressed()), this, SLOT(onRemoveFileType()));
    QObject::connect(ui->fileTypeListWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(onFileTypeChanged(QListWidgetItem*)));
    QObject::connect(ui->fileTypeListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(onFileTypeSelectionChanged(int)));
    QObject::connect(ui->newFileTypeLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onFileTypeLineEditChanged()));

    // Connections of name scheme section
    QObject::connect(ui->newNameSchemeAddButton, SIGNAL(pressed()), this, SLOT(onAddNameScheme()));
    QObject::connect(keyPressEaterEnterNameScheme, SIGNAL(keyPressed()), this, SLOT(onAddNameScheme()));
    QObject::connect(ui->nameSchemeRemoveButton, SIGNAL(pressed()), this, SLOT(onRemoveNameScheme()));
    QObject::connect(keyPressEaterDeleteNameScheme, SIGNAL(keyPressed()), this, SLOT(onRemoveNameScheme()));
    QObject::connect(ui->nameSchemeListWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(onNameSchemeChanged(QListWidgetItem*)));
    QObject::connect(ui->nameSchemeListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(onNameSchemeSelectionChanged(int)));
    QObject::connect(ui->newNameSchemeLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onNameSchemeLineEditChanged()));
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
    delete keyPressEaterDeleteNameScheme;
    delete keyPressEaterEnterNameScheme;
    delete keyPressEaterDeleteFileType;
    delete keyPressEaterEnterFileType;
}

void SettingsWindow::notify(Message &msg)
{
    switch (msg.type) {
    case Message::controller_showSettingsWindow_settings:
    {
        this->show();
        this->setFocus();
        ui->doneButton->setFocus();
        this->setWindowIcon(QIcon(":/images/settings.png"));
        break;
    }
    case Message::controller_changeLocalization_view:
    {
        QString language = *msg.data[1].qsPointer;
        int indexOfLanguage = ui->selectInterfaceLanguageComboBox->findText(language);
        ui->selectInterfaceLanguageComboBox->setCurrentIndex(indexOfLanguage);

        QStringList translationList = *msg.data[0].qsListPointer;
        changeLocalization(translationList);
        break;
    }
    case Message::controller_addGUILanguages_settings:
    {
        QStringList guiLanguageList = *msg.data[0].qsListPointer;
        for (int i = 0; i < guiLanguageList.size(); i++)
            ui->selectInterfaceLanguageComboBox->addItem(guiLanguageList.at(i));
        break;
    }
    case Message::controller_noGUILanguagesFound_settings:
    {
        ui->selectInterfaceLanguageComboBox->setEnabled(false);
        break;
    }
    case Message::controller_changeSeriesParser_view:
    {
        int seriesParser = msg.data[0].i;
        switch(seriesParser)
        {
        default:
        case SeriesParser::tmdb:
        {
            ui->tmdbRadioButton->setChecked(true);
            break;
        }
        case SeriesParser::omdb:
        {
            ui->omdbRadioButton->setChecked(true);
            break;
        }
        case SeriesParser::tvdb:
        {
            ui->tvdbRadioButton->setChecked(true);
            break;
        }
        }
        break;
    }
    case Message::controller_saveSeries_settings:
    {
        bool saveSeries = msg.data[0].b;
        ui->saveSeriesCheckBox->setChecked(saveSeries);
        break;
    }
    case Message::controller_savePath_settings:
    {
        bool savePath = msg.data[0].b;
        ui->savePathCheckBox->setChecked(savePath);
        break;
    }
    case Message::controller_savePoster_settings:
    {
        bool savePoster = msg.data[0].b;
        ui->savePosterCheckBox->setChecked(savePoster);
        break;
    }
    case Message::controller_setDetectedSeason_settings:
    {
        bool setDetectedSeason = msg.data[0].b;
        ui->autoSetDetectedSeasonCheckBox->setChecked(setDetectedSeason);
        break;
    }
    case Message::controller_useDarkTheme_settings:
    {
        bool useDarkTheme = msg.data[0].b;
        ui->darkThemeCheckBox->setChecked(useDarkTheme);
        break;
    }
    case Message::controller_showSeriesInfo_settings:
    {
        bool showSeriesInfo = msg.data[0].b;
        ui->showSeriesInformationCheckBox->setChecked(showSeriesInfo);
        break;
    }
    case Message::controller_setRawNameSchemes_settings:
    {
        QStringList nameSchemes = *msg.data[0].qsListPointer;
        ui->nameSchemeListWidget->clear();
        ui->nameSchemeListWidget->addItems(nameSchemes);
        for (int i = 0; i < nameSchemes.size(); i++)
        {
            QListWidgetItem *item = ui->nameSchemeListWidget->item(i);
            item->setFlags(item->flags() | Qt::ItemIsEditable);
        }
        break;
    }
    case Message::controller_addRawNameScheme_settings:
    {
        QString nameScheme = *msg.data[0].qsPointer;
        ui->nameSchemeListWidget->addItem(nameScheme);
        int lastIndex = ui->nameSchemeListWidget->count() - 1;
        QListWidgetItem *item = ui->nameSchemeListWidget->item(lastIndex);
        item->setFlags(item->flags() | Qt::ItemIsEditable);

        ui->nameSchemeListWidget->setCurrentItem(item);
        break;
    }
    case Message::controller_removeNameScheme_view:
    {
        int index = msg.data[0].i;
        QListWidgetItem *item = ui->nameSchemeListWidget->takeItem(index);
        delete item;
        break;
    }
    case Message::controller_setFileTypes_settings:
    {
        QStringList fileTypes = *msg.data[0].qsListPointer;
        setFileTypeList(fileTypes);
        break;
    }
    case Message::controller_addFileType_settings:
    case Message::controller_replaceFileType_settings:
    {
        int index = msg.data[0].i;
        QStringList fileTypes = *msg.data[1].qsListPointer;
        setFileTypeList(fileTypes);
        ui->fileTypeListWidget->setCurrentRow(index);
        break;
    }
    case Message::controller_removeFileType_settings:
    {
        int index = msg.data[0].i;
        QListWidgetItem *item = ui->fileTypeListWidget->takeItem(index);
        delete item;
        break;
    }
    default:
        break;
    }
}

void SettingsWindow::changeLocalization(QStringList translationList)
{
    this->setWindowTitle(translationList.at(LanguageData::settings));
    ui->tabWidget->setTabText(0, translationList.at(LanguageData::general));
    ui->tabWidget->setTabText(1, translationList.at(LanguageData::video));
    ui->tabWidget->setTabText(2, translationList.at(LanguageData::nameScheme));
    ui->resetButton->setText(translationList.at(LanguageData::reset));
    ui->doneButton->setText(translationList.at(LanguageData::done));
    ui->interfaceGroupBox->setTitle(translationList.at(LanguageData::interface));
    ui->languageLabel->setText(translationList.at(LanguageData::language));
    ui->darkThemeCheckBox->setText(translationList.at(LanguageData::darkTheme));
    ui->showSeriesInformationCheckBox->setText(translationList.at(LanguageData::showSeriesInformation));
    ui->saveOnExitGroupBox->setTitle(translationList.at(LanguageData::saveOnExit));
    ui->savePathCheckBox->setText(translationList.at(LanguageData::path));
    ui->saveSeriesCheckBox->setText(translationList.at(LanguageData::series));
    ui->seriesDatabaseGroupBox->setTitle(translationList.at(LanguageData::seriesDatabase));
    ui->recommendLabel->setText(translationList.at(LanguageData::recommended));
    ui->saveInDirectoryGroupBox->setTitle(translationList.at(LanguageData::saveInSeriesDirectory));
    ui->savePosterCheckBox->setText(translationList.at(LanguageData::poster));
    ui->miscGroupBox->setTitle(translationList.at(LanguageData::miscellaneous));
    ui->autoSetDetectedSeasonCheckBox->setText(translationList.at(LanguageData::setDetectedSeason));
    ui->videoGroupBox->setTitle(translationList.at(LanguageData::newFormat));
    ui->newFileTypeAddButton->setText(translationList.at(LanguageData::add));
    ui->fileTypeRemoveButton->setText(translationList.at(LanguageData::remove));
    ui->newNameSchemeGroupBox->setTitle(translationList.at(LanguageData::newNameScheme));
    ui->newNameSchemeAddButton->setText(translationList.at(LanguageData::add));
    ui->nameSchemeRemoveButton->setText(translationList.at(LanguageData::remove));
    // Reset confirmation dialog
    resetConfirmationMessageBox.setWindowTitle(translationList.at(LanguageData::areYouSure));
    resetConfirmationMessageBox.setText(translationList.at(LanguageData::areYouSureDetailed));
    resetConfirmationMessageBox.setButtonText(0, translationList.at(LanguageData::yes));
    resetConfirmationMessageBox.setButtonText(1, translationList.at(LanguageData::no));
}

void SettingsWindow::createResetConfirmationDialog()
{
    resetConfirmationMessageBox.setWindowTitle("Are you sure?");
    resetConfirmationMessageBox.setText("Are you sure? All settings will be reset to default. This cannot be undone.");
    resetConfirmationMessageBox.addButton("Yes", QMessageBox::YesRole);
    resetConfirmationMessageBox.addButton("No", QMessageBox::NoRole);
    resetConfirmationMessageBox.setDefaultButton(QMessageBox::No);
}

void SettingsWindow::resizeNameSchemeTab()
{
    int tabWidth = this->width() - UNIVERSAL_SPACER;
    int tabHeight = windowSize.height() - 60;
    int listWidth = tabWidth - 2.5 * UNIVERSAL_SPACER;
    int listHeight = ui->nameSchemeListWidget->height();
    int groupBoxHeight = ui->newNameSchemeGroupBox->height();
    int removeButtonX = listWidth - ui->nameSchemeRemoveButton->width() - 0.5 * UNIVERSAL_SPACER;
    int removeButtonY = ui->nameSchemeRemoveButton->y();
    int addButtonX = removeButtonX - ui->newNameSchemeAddButton->width();
    int addButtonY = ui->newNameSchemeAddButton->y();
    int lineEditWidth = addButtonX - 2 * UNIVERSAL_SPACER;
    int lineEditHeight = ui->newNameSchemeLineEdit->height();

    ui->nameSchemeListWidget->resize(listWidth, listHeight);
    ui->tabWidget->resize(tabWidth, tabHeight);
    ui->newNameSchemeGroupBox->resize(listWidth, groupBoxHeight);
    ui->newNameSchemeLineEdit->resize(lineEditWidth, lineEditHeight);
    ui->nameSchemeRemoveButton->move(removeButtonX, removeButtonY);
    ui->newNameSchemeAddButton->move(addButtonX, addButtonY);
}

void SettingsWindow::setFileTypeList(QStringList fileTypes)
{
    ui->fileTypeListWidget->clear();
    ui->fileTypeListWidget->addItems(fileTypes);

    for (int i = 0; i < fileTypes.size(); i++)
    {
        QListWidgetItem *item = ui->fileTypeListWidget->item(i);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setSizeHint(QSize(90,18));
        item->setTextAlignment(Qt::AlignLeft);
    }
}

void SettingsWindow::onGUILanguageChanged(QString language)
{
    Message msgChangeGUILanguage;
    msgChangeGUILanguage.type = Message::settings_changeGUILanguage_controller;
    msgChangeGUILanguage.data[0].qsPointer = &language;
    emit(sendMessage(msgChangeGUILanguage));
}

void SettingsWindow::onSeriesParserChanged()
{
    bool tmdb = ui->tmdbRadioButton->isChecked();
    bool omdb = ui->omdbRadioButton->isChecked();
    bool tvdb = ui->tvdbRadioButton->isChecked();

    Message msgSeriesParserChanged;
    msgSeriesParserChanged.type = Message::settings_changeSeriesParser_controller;
    if (tmdb)
        msgSeriesParserChanged.data[0].i = SeriesParser::tmdb;
    else if (omdb)
        msgSeriesParserChanged.data[0].i = SeriesParser::omdb;
    else if (tvdb)
        msgSeriesParserChanged.data[0].i = SeriesParser::tvdb;
    else // Should never happen
        msgSeriesParserChanged.data[0].i = SeriesParser::tmdb;
    emit(sendMessage(msgSeriesParserChanged));
}

void SettingsWindow::onSaveSeriesChanged(bool saveSeries)
{
    Message msgSaveSeries;
    msgSaveSeries.type = Message::settings_saveSeries_controller;
    msgSaveSeries.data[0].b = saveSeries;
    emit(sendMessage(msgSaveSeries));
}

void SettingsWindow::onSavePathChanged(bool savePath)
{
    Message msgSavePath;
    msgSavePath.type = Message::settings_savePath_controller;
    msgSavePath.data[0].b = savePath;
    emit(sendMessage(msgSavePath));
}

void SettingsWindow::onSavePosterChanged(bool savePoster)
{
    Message msgSavePoster;
    msgSavePoster.type = Message::settings_savePoster_controller;
    msgSavePoster.data[0].b = savePoster;
    emit(sendMessage(msgSavePoster));
}

void SettingsWindow::onSetDetectedSeason(bool setDetectedSeason)
{
    Message msgSetDetectedSeason;
    msgSetDetectedSeason.type = Message::settings_setDetectedSeason_controller;
    msgSetDetectedSeason.data[0].b = setDetectedSeason;
    emit(sendMessage(msgSetDetectedSeason));
}

void SettingsWindow::onResetClicked()
{
    resetConfirmationMessageBox.setFocus();
    if (resetConfirmationMessageBox.exec() == 0) // 0 = Yes button
    {
        Message msgResetSettings;
        msgResetSettings.type = Message::settings_reset_controller;
        emit(sendMessage(msgResetSettings));
    }
}

void SettingsWindow::onDarkThemeChanged(bool useDarkTheme)
{
    Message msgChangeDarkTheme;
    msgChangeDarkTheme.type = Message::settings_useDarkTheme_controller;
    msgChangeDarkTheme.data[0].b = useDarkTheme;
    emit(sendMessage(msgChangeDarkTheme));
}

void SettingsWindow::onShowSeriesInformationChanged(bool showInfo)
{
    Message msgChangeShowSeriesInfo;
    msgChangeShowSeriesInfo.type = Message::settings_showSeriesInfo_controller;
    msgChangeShowSeriesInfo.data[0].b = showInfo;
    emit(sendMessage(msgChangeShowSeriesInfo));
}

void SettingsWindow::onTabChanged(int index)
{
    if (index == 2) // Name Scheme tab
    {
        int windowWidth = ui->nameSchemeListWidget->sizeHintForColumn(0) + 2 * UNIVERSAL_SPACER + 20;
        if (windowWidth > 1000)
            windowWidth = 1000;
        else if (windowWidth < windowSize.width())
            windowWidth = windowSize.width();

        QSize newSize(windowWidth, this->height());
        this->resize(newSize);
        this->setMinimumSize(newSize);
        this->setMaximumSize(newSize);
        resizeNameSchemeTab();
    } else
    {
        this->resize(windowSize);
        this->setMinimumSize(windowSize);
        this->setMaximumSize(windowSize);
        ui->tabWidget->resize(windowSize.width() - UNIVERSAL_SPACER, windowSize.height() - 60);
    }
    int doneButtonX = this->width() - ui->doneButton->width() - UNIVERSAL_SPACER;
    int doneButtonY = ui->doneButton->y();
    ui->doneButton->move(doneButtonX, doneButtonY);
}

void SettingsWindow::onAddNameScheme()
{
    QString newNameScheme = ui->newNameSchemeLineEdit->text();
    if (newNameScheme.isEmpty())
        return;
    ui->newNameSchemeLineEdit->clear();

    Message msgAddNameScheme;
    msgAddNameScheme.type = Message::settings_addNameScheme_controller;
    msgAddNameScheme.data[0].qsPointer = &newNameScheme;
    emit(sendMessage(msgAddNameScheme));
}

void SettingsWindow::onRemoveNameScheme()
{
    int index = ui->nameSchemeListWidget->currentIndex().row();
    if (index >= 0)
    {
        Message msgRemoveNameScheme;
        msgRemoveNameScheme.type = Message::settings_removeNameScheme_controller;
        msgRemoveNameScheme.data[0].i = index;
        emit(sendMessage(msgRemoveNameScheme));
    }
}

void SettingsWindow::onNameSchemeChanged(QListWidgetItem *item)
{
    if (ui->newNameSchemeLineEdit->hasFocus()) // Workaround: list widget catches all key events
        return;

    int index = ui->nameSchemeListWidget->currentIndex().row();
    if (index >= 0)
    {
        QString changedNameScheme = item->text();

        Message msgReplaceNameScheme;
        msgReplaceNameScheme.type = Message::settings_replaceNameScheme_controller;
        msgReplaceNameScheme.data[0].i = index;
        msgReplaceNameScheme.data[1].qsPointer = &changedNameScheme;
        emit(sendMessage(msgReplaceNameScheme));
    }
}

void SettingsWindow::onNameSchemeSelectionChanged(int index)
{
    bool positiveIndex = (index >= 0);
    ui->nameSchemeRemoveButton->setEnabled(positiveIndex);
}


void SettingsWindow::onNameSchemeLineEditChanged()
{
    bool lineEditIsEmpty = ui->newNameSchemeLineEdit->text().isEmpty();
    ui->newNameSchemeAddButton->setEnabled(!lineEditIsEmpty);
}

void SettingsWindow::onAddFileType()
{
    QString newFileType = ui->newFileTypeLineEdit->text();
    if (newFileType.isEmpty())
        return;
    ui->newFileTypeLineEdit->clear();

    Message msgAddFileType;
    msgAddFileType.type = Message::settings_addFileType_controller;
    msgAddFileType.data[0].qsPointer = &newFileType;
    emit(sendMessage(msgAddFileType));
}

void SettingsWindow::onRemoveFileType()
{
    int index = ui->fileTypeListWidget->currentIndex().row();
    if (index >= 0)
    {
        Message msgRemoveFileType;
        msgRemoveFileType.type = Message::settings_removeFileType_controller;
        msgRemoveFileType.data[0].i = index;
        emit(sendMessage(msgRemoveFileType));
    }
}

void SettingsWindow::onFileTypeChanged(QListWidgetItem *item)
{
    if (ui->newFileTypeLineEdit->hasFocus()) // Workaround: list widget catches all key events
        return;

    int index = ui->fileTypeListWidget->currentIndex().row();
    if (index >= 0)
    {
        QString changedFileType = item->text();
        qDebug() << changedFileType;
        Message msgChangeFileType;
        msgChangeFileType.type = Message::settings_replaceFileType_controller;
        msgChangeFileType.data[0].i = index;
        msgChangeFileType.data[1].qsPointer = &changedFileType;
        emit(sendMessage(msgChangeFileType));
    }
}

void SettingsWindow::onFileTypeSelectionChanged(int index)
{
    bool positiveIndex = (index >= 0);
    ui->fileTypeRemoveButton->setEnabled(positiveIndex);
}

void SettingsWindow::onFileTypeLineEditChanged()
{
    bool lineEditIsEmpty = ui->newFileTypeLineEdit->text().isEmpty();
    ui->newFileTypeAddButton->setEnabled(!lineEditIsEmpty);
}
