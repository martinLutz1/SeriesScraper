#define APPLICATIONNAME "SeriesScraper"

#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "languagedata.h" // To lookup enum
#include "QDebug"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(hide()));
    window()->setWindowIcon(QIcon(":/images/about.png"));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::notify(Message &msg)
{
    switch (msg.type) {
    case Message::controller_showAboutDialog_about:
    {
        this->show();
        this->setWindowIcon(QIcon(":/images/about.png"));
        break;
    }
    case Message::controller_changeLocalization_view:
    {
        QStringList translationList = *msg.data[0].qsListPointer;
        ui->closeButton->setText(translationList.at(LanguageData::close));
        this->setWindowTitle(translationList.at(LanguageData::about) + " " + APPLICATIONNAME);
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
