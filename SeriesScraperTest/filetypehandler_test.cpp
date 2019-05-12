#include <QStringList>

#include "filetypehandler_test.h"
#include "filetypehandler.h"

void FileTypeHandlerTest::FileTypeHandler_addFileType()
{
    FileTypeHandler fileTypeHandler;
    QCOMPARE(0, fileTypeHandler.getFileTypes().size());

    fileTypeHandler.addFileType("avi");
    QCOMPARE(QStringList({"avi"}), fileTypeHandler.getFileTypes());

    fileTypeHandler.addFileType("mkv");
    QCOMPARE(QStringList({"avi", "mkv"}), fileTypeHandler.getFileTypes());
}

void FileTypeHandlerTest::FileTypeHandler_removeFileType()
{
    auto addFileTypes = [](
            FileTypeHandler& fileTypeHandler,
            const QStringList& fileTypes)
    {
        for (const auto& fileType : fileTypes)
        {
            fileTypeHandler.addFileType(fileType);
        }
    };

    // Remove existing elements.
    {
        FileTypeHandler fileTypeHandler;
        const auto fileTypes = QStringList({"aaa", "bbb", "ccc"});
        addFileTypes(fileTypeHandler, fileTypes);
        QCOMPARE(fileTypes, fileTypeHandler.getFileTypes());

        fileTypeHandler.removeFileType(2);
        QCOMPARE(QStringList({"aaa", "bbb"}), fileTypeHandler.getFileTypes());

        fileTypeHandler.removeFileType(2);
        QCOMPARE(QStringList({"aaa", "bbb"}), fileTypeHandler.getFileTypes());

        fileTypeHandler.removeFileType(0);
        QCOMPARE(QStringList({"bbb"}), fileTypeHandler.getFileTypes());

        fileTypeHandler.removeFileType(0);
        QCOMPARE(QStringList(), fileTypeHandler.getFileTypes());
    }

    // Remove from an empty list
    {
        FileTypeHandler fileTypeHandler;

        fileTypeHandler.removeFileType(0);
        QCOMPARE(QStringList(), fileTypeHandler.getFileTypes());

        fileTypeHandler.removeFileType(20);
        QCOMPARE(QStringList(), fileTypeHandler.getFileTypes());
    }
}
