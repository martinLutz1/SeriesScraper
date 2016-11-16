#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T15:59:01
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += script
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SeriesScraper
TEMPLATE = app

SOURCES += main.cpp \
        mainwindow.cpp \
    directoryparser.cpp \
    application.cpp \
    languagedata.cpp \
    languagecontrol.cpp \
    controller.cpp \
    seriesdata.cpp \
    message.cpp \
    filerenamer.cpp \
    nameschemeparser.cpp \
    nameschemehandler.cpp \
    omdbseriesparser.cpp \
    tmdbseriesparser.cpp \
    jsonscraper.cpp \
    serieslanguage.cpp \
    aboutdialog.cpp \
    settingswindow.cpp

HEADERS  += mainwindow.h \
    directoryparser.h \
    application.h \
    languagedata.h \
    languagecontrol.h \
    controller.h \
    seriesdata.h \
    message.h \
    filerenamer.h \
    nameschemeparser.h \
    nameschemehandler.h \
    omdbseriesparser.h \
    tmdbseriesparser.h \
    jsonscraper.h \
    serieslanguage.h \
    aboutdialog.h \
    settingswindow.h

macx {
    # Deploying
    QMAKE_POST_LINK += ~/Qt/5.7/clang_64/bin/macdeployqt SeriesScraper.app;
    # Copy namescheme list, language folder and series language list
    QMAKE_POST_LINK += cp -Rf ./../deployment_files/* ./SeriesScraper.app/Contents/MacOs;
}
unix:!macx {
    QMAKE_POST_LINK += cp -Rf ./../deployment_files/* ./;
}


FORMS    += mainwindow.ui \
    aboutdialog.ui \
    settingswindow.ui

RESOURCES += \
    resource.qrc

CONFIG += c++11
QMAKE_MAC_SDK = macosx10.12