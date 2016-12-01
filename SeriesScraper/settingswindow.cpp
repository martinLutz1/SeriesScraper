#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "languagedata.h"
#include "seriesparser.h"
#include <QDebug>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    createResetConfirmationDialog();
    QObject::connect(ui->doneButton, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(ui->selectInterfaceLanguageComboBox, SIGNAL(activated(QString)), this, SLOT(onGUILanguageChanged(QString)));
    QObject::connect(ui->tmdbRadioButton, SIGNAL(clicked(bool)), this, SLOT(onSeriesParserChanged()));
    QObject::connect(ui->omdbRadioButton, SIGNAL(clicked(bool)), this, SLOT(onSeriesParserChanged()));
    QObject::connect(ui->saveSeriesCheckBox, SIGNAL(toggled(bool)), this, SLOT(onSaveSeriesChanged(bool)));
    QObject::connect(ui->savePathCheckBox, SIGNAL(toggled(bool)), this, SLOT(onSavePathChanged(bool)));
    QObject::connect(ui->resetButton, SIGNAL(pressed()), this, SLOT(onResetClicked()));
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::notify(Message &msg)
{
    switch (msg.type) {
    case Message::controller_showSettingsWindow_settings:
    {
        this->show();
        this->setFocus();
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
    ui->showSeriesInformationCheckBox->setText(translationList.at(LanguageData::showSeriesInformation));
    ui->saveOnExitGroupBox->setTitle(translationList.at(LanguageData::saveOnExit));
    ui->savePathCheckBox->setText(translationList.at(LanguageData::path));
    ui->saveSeriesCheckBox->setText(translationList.at(LanguageData::series));
    ui->seriesDatabaseGroupBox->setTitle(translationList.at(LanguageData::seriesDatabase));
    ui->recommendLabel->setText(translationList.at(LanguageData::recommended));
    ui->newFormatGroupBox->setTitle(translationList.at(LanguageData::newFormat));
    ui->newFormatAddButton->setText(translationList.at(LanguageData::add));
    ui->formatRemoveButton->setText(translationList.at(LanguageData::remove));
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

    Message msgSeriesParserChanged;
    msgSeriesParserChanged.type = Message::settings_changeSeriesParser_controller;
    if (tmdb)
        msgSeriesParserChanged.data[0].i = 0;
    else if (omdb)
        msgSeriesParserChanged.data[0].i = 1;
    else // Should never happen
        msgSeriesParserChanged.data[0].i = 0;
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
