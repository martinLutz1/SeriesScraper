#ifndef KEYPRESSEATER_H
#define KEYPRESSEATER_H

#include <QObject>

class KeyPressEater : public QObject
{
    Q_OBJECT

public:
    KeyPressEater();
    void setKey(int key);

private:
    int key;

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void keyPressed();
};

#endif // KEYPRESSEATER_H
