CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

QT += testlib core network widgets
QT -= gui

VPATH += ../SeriesScraper/src

SOURCES += \
    testdirectoryhandler.cpp \
    testfiletypehandler.cpp

HEADERS += \
    testdirectoryhandler.h \
    testfiletypehandler.h

include(../SeriesScraper/SeriesScraperSrc.pri)
