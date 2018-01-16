greaterThan(QT_MAJOR_VERSION, 4)

TARGET = SeriesScraper
TEMPLATE += app

CONFIG += c++14
QT += core gui network widgets
DEFINES += QT_DEPRECATED_WARNINGS


VPATH += ./src
SOURCES += \
    main.cpp \
    application.cpp \
    mainwindow.cpp \
    aboutdialog.cpp \
    settingswindow.cpp

 HEADERS += \
    application.h \
    mainwindow.h \
    aboutdialog.h \
    settingswindow.h

include(SeriesScraperAppSrc.pri)

FORMS += \
    forms/mainwindow.ui \
    forms/aboutdialog.ui \
    forms/settingswindow.ui

RESOURCES += \
    images/resource.qrc

##### PLATFORM SPECIFIC DEPLOYMENT #####
#--------------------------------------#
win32 {
    RC_FILE = images/app_logo/winIcon.rc
    LIBS += -L"C:/git/SeriesScraper/SeriesScraperApp/libraries" -llibeay32
}

macx {
    debug {
        #CONFIG -= app_bundle
    }
    QMAKE_MAC_SDK = macosx10.13
    ICON = images/app_logo/macIcon.icns

    QMAKE_POST_LINK += ~/Qt5.10.0/5.10.0/clang_64/bin/macdeployqt SeriesScraper.app;
    QMAKE_POST_LINK += cp -Rf ./../DeploymentFiles/general/* ./SeriesScraper.app/Contents/MacOs;
    QMAKE_POST_LINK += cp -Rf ./../DeploymentFiles/mac/Info.plist ./SeriesScraper.app/Contents;
}

unix:!macx {
    QMAKE_POST_LINK += cp -Rf ./../deployment_files/general/* ./;
}
