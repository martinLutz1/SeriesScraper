#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
}

AboutDialog::~AboutDialog()
{
    delete ui;
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

void AboutDialog::closeWindow()
{
    this->hide();
}
