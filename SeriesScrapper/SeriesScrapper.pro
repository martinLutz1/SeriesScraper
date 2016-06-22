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

SOURCES += main.cpp\
        mainwindow.cpp \
    control.cpp \
    jsonparser.cpp \
    directoryparser.cpp

HEADERS  += mainwindow.h \
    control.h \
    jsonparser.h \
    directoryparser.h

FORMS    += mainwindow.ui
