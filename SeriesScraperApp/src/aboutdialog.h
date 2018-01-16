#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include "message.h"

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

public slots:
    void notify(Message &msg);

private:
    Ui::AboutDialog *ui;
    void resizeEvent(QResizeEvent *event);
};

#endif // ABOUTDIALOG_H
