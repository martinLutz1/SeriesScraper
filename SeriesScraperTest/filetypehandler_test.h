#include <QtTest/QtTest>

#include "TestCollector.h"

class FileTypeHandlerTest : public QObject
{
    Q_OBJECT

private slots:
    void FileTypeHandler_addFileType();
    void FileTypeHandler_removeFileType();
};

ADD_TEST(FileTypeHandlerTest)
