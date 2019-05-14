SOURCES += \
    main.cpp \
    directoryparser_test.cpp \
    filetypehandler_test.cpp

HEADERS += \
    TestCollector.h \
    directoryparser_test.h \
    filetypehandler_test.h

CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += TEST_EXE_DIR='\\"$$OUT_PWD\\"'

QT += testlib core network widgets
QT -= gui

INCLUDEPATH += $$PWD/../SeriesScraperLib/src
DEPENDPATH += $$PWD/../SeriesScraperLib

unix|win32: LIBS += -L$$PWD/../BuildSeriesScraperLib/ -lSeriesScraperLib
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../BuildSeriesScraperLib/SeriesScraperLib.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../BuildSeriesScraperLib/libSeriesScraperLib.a

#Deploy test files
QMAKE_POST_LINK += cp -Rf $$PWD/../SeriesScraperTest/TestFiles/ $$OUT_PWD/TestFiles;
