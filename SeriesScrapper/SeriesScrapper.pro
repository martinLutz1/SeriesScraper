#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T15:59:01
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += script
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SeriesScrapper
TEMPLATE = app

SOURCES += main.cpp \
        mainwindow.cpp \
    jsonparser.cpp \
    directoryparser.cpp \
    application.cpp \
    languagedata.cpp \
    languagecontrol.cpp

HEADERS  += mainwindow.h \
    jsonparser.h \
    directoryparser.h \
    application.h \
    languagedata.h \
    languagecontrol.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
