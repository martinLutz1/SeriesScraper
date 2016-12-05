#include "keypresseater.h"

#include <QtGui>
#include <QtCore>

KeyPressEater::KeyPressEater() : key(0)
{
}

void KeyPressEater::setKey(int key)
{
    this->key = key;
}

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress && (static_cast<QKeyEvent *>(event))->key() == key) {
        emit keyPressed();
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
