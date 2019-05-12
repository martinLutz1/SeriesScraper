#include <QtTest/QtTest>

#include "TestCollector.h"

class DirectoryHandlerTest: public QObject
{
    Q_OBJECT

private slots:
    void DirectoryHandler_foo();
};

ADD_TEST(DirectoryHandlerTest)
