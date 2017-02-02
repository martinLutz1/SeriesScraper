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
    controller.cpp \
    seriesdata.cpp \
    message.cpp \
    filerenamer.cpp \
    nameschemeparser.cpp \
    nameschemehandler.cpp \
    omdbseriesparser.cpp \
    tmdbseriesparser.cpp \
    jsonscraper.cpp \
    aboutdialog.cpp \
    settingswindow.cpp \
    error.cpp \
    settings.cpp \
    jsonloader.cpp \
    seriesparser.cpp \
    seriesfilesaver.cpp \
    customshadoweffect.cpp \
    keypresseater.cpp \
    rawloader.cpp \
    filetypehandler.cpp \
    serieslanguagehandler.cpp \
    interfacelanguagehandler.cpp \
    baseseriesparser.cpp \
    filedownloader.cpp

HEADERS  += mainwindow.h \
    directoryparser.h \
    application.h \
    languagedata.h \
    controller.h \
    seriesdata.h \
    message.h \
    filerenamer.h \
    nameschemeparser.h \
    nameschemehandler.h \
    omdbseriesparser.h \
    tmdbseriesparser.h \
    jsonscraper.h \
    aboutdialog.h \
    settingswindow.h \
    error.h \
    settings.h \
    jsonloader.h \
    seriesparser.h \
    seriesfilesaver.h \
    customshadoweffect.h \
    keypresseater.h \
    rawloader.h \
    filetypehandler.h \
    serieslanguagehandler.h \
    interfacelanguagehandler.h \
    baseseriesparser.h \
    filedownloader.h

win32 {
    RC_FILE = images/icon/winIcon.rc
    LIBS += -L"C:\git\SeriesScraper\SeriesScraper\libraries" -llibeay32
}
macx {
    ICON = images/icon/macIcon.icns
    # Deploying
    QMAKE_POST_LINK += ~/Qt/5.7/clang_64/bin/macdeployqt SeriesScraper.app;
    # Copy namescheme list, language folder, series language list and file type list
    QMAKE_POST_LINK += cp -Rf ./../deployment_files/general/* ./SeriesScraper.app/Contents/MacOs;
    # Copy info.plist
    QMAKE_POST_LINK += cp -Rf ./../deployment_files/mac/Info.plist ./SeriesScraper.app/Contents;
}
unix:!macx {
    QMAKE_POST_LINK += cp -Rf ./../deployment_files/general/* ./;
}


FORMS    += mainwindow.ui \
    aboutdialog.ui \
    settingswindow.ui

RESOURCES += \
    resource.qrc

CONFIG += c++11
QMAKE_MAC_SDK = macosx10.12
