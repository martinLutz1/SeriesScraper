#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "languagedata.h" // Translate enum
#include <QDebug>
#include <QCoreApplication>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->nameAndVersionLabel->setText(QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion());

    QObject::connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(hide()));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::notify(Message &msg)
{
    switch (msg.type) {
    case Message::Type::controller_showAboutDialog_about:
    {
        this->show();
        this->setWindowIcon(QIcon(":/ui_icons/about.png"));
        break;
    }
    case Message::Type::controller_changeLocalization_view:
    {
        QStringList translationList = *msg.data[0].qsListPointer;
        ui->closeButton->setText(translationList.at(static_cast<int>(LanguageData::Translate::close)));
        this->setWindowTitle(translationList.at(static_cast<int>(LanguageData::Translate::about)) + " " + QCoreApplication::applicationName());
        break;
    }
    default:
        break;
    }
}

void AboutDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    int windowWidth = this->width();
    int buttonWidth = ui->closeButton->width();
    int buttonY = ui->closeButton->y();
    int buttonX = windowWidth / 2 - buttonWidth / 2;

    ui->closeButton->move(buttonX, buttonY);
}
