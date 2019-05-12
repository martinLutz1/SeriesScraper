CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

QT += testlib core network widgets
QT -= gui

INCLUDEPATH += $$PWD/../SeriesScraperLib/src
DEPENDPATH += $$PWD/../SeriesScraperLib

unix|win32: LIBS += -L$$PWD/../BuildSeriesScraperLib/ -lSeriesScraperLib
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../BuildSeriesScraperLib/SeriesScraperLib.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../BuildSeriesScraperLib/libSeriesScraperLib.a

SOURCES += \
    main.cpp \
    directoryhandler_test.cpp \
    filetypehandler_test.cpp

HEADERS += \
    TestCollector.h \
    directoryhandler_test.h \
    filetypehandler_test.h
