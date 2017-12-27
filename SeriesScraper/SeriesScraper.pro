#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T15:59:01
#
#-------------------------------------------------
greaterThan(QT_MAJOR_VERSION, 4)

QT += core gui
QT += network
QT += widgets

CONFIG += c++14

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
    basefiledownloader.cpp \
    tvdbseriesparser.cpp \
    directoryhandler.cpp \
    QProgressIndicator.cpp \
    genericfiledownloader.cpp \
    episodename.cpp \
    episodenamehandler.cpp

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
    basefiledownloader.h \
    tvdbseriesparser.h \
    directoryhandler.h \
    QProgressIndicator.h \
    genericfiledownloader.h \
    episodename.h \
    episodenamehandler.h

FORMS += mainwindow.ui \
    aboutdialog.ui \
    settingswindow.ui

RESOURCES += \
    resource.qrc

win32 {
    RC_FILE = images/icon/winIcon.rc
    LIBS += -L"C:\git\SeriesScraper\SeriesScraper\libraries" -llibeay32
}

macx {
    debug {
        CONFIG -= app_bundle
    }
    QMAKE_MAC_SDK = macosx10.13
    ICON = images/icon/macIcon.icns

    QMAKE_POST_LINK += ~/Qt5.9.3/5.9.3/clang_64/bin/macdeployqt SeriesScraper.app;
    QMAKE_POST_LINK += cp -Rf ./../deployment_files/general/* ./SeriesScraper.app/Contents/MacOs;
    QMAKE_POST_LINK += cp -Rf ./../deployment_files/mac/Info.plist ./SeriesScraper.app/Contents;
}

unix:!macx {
    QMAKE_POST_LINK += cp -Rf ./../deployment_files/general/* ./;
}
