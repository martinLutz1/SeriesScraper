#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "languagedata.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->doneButton, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(ui->selectInterfaceLanguageComboBox, SIGNAL(activated(QString)), this, SLOT(onGUILanguageChanged(QString)));
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
        break;
    }
    case Message::controller_changeLocalization_view:
    {
        QStringList translationList = *msg.data[0].qsListPointer;
        changeLocalization(translationList);
        break;
    }
    case Message::controller_addGUILanguage_settings:
    {
        QString language = *msg.data[0].qsPointer;
        ui->selectInterfaceLanguageComboBox->addItem(language);
        break;
    }
    case Message::controller_noGUILanguagesFound_settings:
    {
        ui->selectInterfaceLanguageComboBox->setEnabled(false);
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
    ui->resetAllButton->setText(translationList.at(LanguageData::resetAll));
    ui->doneButton->setText(translationList.at(LanguageData::done));
    ui->interfaceGroupBox->setTitle(translationList.at(LanguageData::interface));
    ui->languageLabel->setText(translationList.at(LanguageData::language));
    ui->showSeriesInformationCheckBox->setText(translationList.at(LanguageData::showSeriesInformation));
    ui->saveOnExitGroupBox->setTitle(translationList.at(LanguageData::saveOnExit));
    ui->savePathCheckBox->setText(translationList.at(LanguageData::path));
    ui->saveSeriesCheckBox->setText(translationList.at(LanguageData::series));
    ui->seriesDatabaseGroupBox->setTitle(translationList.at(LanguageData::seriesDatabase));
    ui->recommendLabel->setText(translationList.at(LanguageData::recommended));
    ui->generalResetButton->setText(translationList.at(LanguageData::reset));
    ui->newFormatGroupBox->setTitle(translationList.at(LanguageData::newFormat));
    ui->newFormatAddButton->setText(translationList.at(LanguageData::add));
    ui->formatRemoveButton->setText(translationList.at(LanguageData::remove));
    ui->videoResetButton->setText(translationList.at(LanguageData::reset));
    ui->newNameSchemeGroupBox->setTitle(translationList.at(LanguageData::newNameScheme));
    ui->newNameSchemeAddButton->setText(translationList.at(LanguageData::add));
    ui->nameSchemeRemoveButton->setText(translationList.at(LanguageData::remove));
    ui->nameSchemeResetButton->setText(translationList.at(LanguageData::reset));
}

void SettingsWindow::onGUILanguageChanged(QString language)
{
    Message msgChangeGUILanguage;
    msgChangeGUILanguage.type = Message::settings_changeGUILanguage_controller;
    msgChangeGUILanguage.data[0].qsPointer = &language;
    emit(sendMessage(msgChangeGUILanguage));
}
