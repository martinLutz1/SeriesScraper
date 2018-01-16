TEMPLATE = lib
CONFIG += staticlib c++14

QT += core network
DEFINES += QT_DEPRECATED_WARNINGS

include(SeriesScraperLibSrc.pri)

QMAKE_POST_LINK += mkdir $$PWD/../BuildSeriesScraperLib;
QMAKE_POST_LINK += cp -Rf $$OUT_PWD/libSeriesScraperLib.* $$PWD/../BuildSeriesScraperLib/;
