#include "directoryparser_test.h"

#include <QDir>
#include "directoryparser.h"

void DirectoryParserTest::DirectoryParser_initializeDirectory_NoCrashOnUnknownPositions()
{
    DirectoryParser directoryParser;
    directoryParser.setFileTypes({ "mkv" });
    QDir testDirectory(TEST_EXE_DIR);
    testDirectory.cd("TestFiles/3UnknownPositions");

    const auto initSuccessful = directoryParser.initializeDirectory(testDirectory.absolutePath());
    QCOMPARE(initSuccessful, true);

    const auto positions = directoryParser.getFilePositions();
    QCOMPARE(positions.size(), 5);
    QCOMPARE(positions.at(0), EpisodeName::Position::unsure);
    QCOMPARE(positions.at(1), EpisodeName::Position::unsure);
    QCOMPARE(positions.at(2), EpisodeName::Position::unsure);
    QCOMPARE(positions.at(3), EpisodeName::Position::unsure);
    QCOMPARE(positions.at(4), EpisodeName::Position::determined);

    const auto fileNamesWithoutSuffix = directoryParser.getFilesWithoutSuffix();
    QCOMPARE(fileNamesWithoutSuffix.at(0), "file1");
    QCOMPARE(fileNamesWithoutSuffix.at(1), "file2");
    QCOMPARE(fileNamesWithoutSuffix.at(2), "file3");
    QCOMPARE(fileNamesWithoutSuffix.at(3), "");
    QCOMPARE(fileNamesWithoutSuffix.at(4), "fileS01E05");
}
