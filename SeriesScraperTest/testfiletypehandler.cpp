#include "testfiletypehandler.h"
#include "../SeriesScraper/src/filetypehandler.h"

#include <QStringList>

void TestFileTypeHandler::addFileTypes()
{
    FileTypeHandler fileTypeHandler;
    {
        const auto& fileTypes = fileTypeHandler.getFileTypes();
        QCOMPARE(0, fileTypes.size());
    }

    fileTypeHandler.addFileType("avi");
    {
        const auto& fileTypes = fileTypeHandler.getFileTypes();
        const auto expectedFileTypes = QStringList({"avi"});

        QCOMPARE(1, fileTypes.size());
        QCOMPARE(expectedFileTypes, fileTypes);
    }

    fileTypeHandler.addFileType("mkv");
    {
        const auto& fileTypes = fileTypeHandler.getFileTypes();
        const auto expectedFileTypes = QStringList({"avi", "mkv"});

        QCOMPARE(2, fileTypes.size());
        QCOMPARE(expectedFileTypes, fileTypes);
    }
}

QTEST_APPLESS_MAIN(TestFileTypeHandler)
