#include <QtTest/QtTest>

#include "TestCollector.h"

class DirectoryParserTest: public QObject
{
    Q_OBJECT

private slots:
    void DirectoryParser_initializeDirectory_NoCrashOnUnknownPositions();
};

ADD_TEST(DirectoryParserTest)
