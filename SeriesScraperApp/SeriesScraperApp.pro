greaterThan(QT_MAJOR_VERSION, 4)

TARGET = SeriesScraperApp
TEMPLATE += app

CONFIG += c++14
QT += core gui widgets network
DEFINES += QT_DEPRECATED_WARNINGS

##### INCLUDE LIBRARY #####
#--------------------------------------#
INCLUDEPATH += $$PWD/../SeriesScraperLib/src
DEPENDPATH += $$PWD/../SeriesScraperLib

unix|win32: LIBS += -L$$PWD/../BuildSeriesScraperLib/ -lSeriesScraperLib
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../BuildSeriesScraperLib/SeriesScraperLib.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../BuildSeriesScraperLib/libSeriesScraperLib.a


SOURCES += \
    src/main.cpp \
    src/application.cpp \
    src/controller.cpp \
    src/mainwindow.cpp \
    src/aboutdialog.cpp \
    src/settingswindow.cpp \
    src/customshadoweffect.cpp \
    src/QProgressIndicator.cpp

 HEADERS += \
    src/application.h \
    src/controller.h \
    src/mainwindow.h \
    src/aboutdialog.h \
    src/settingswindow.h \
    src/customshadoweffect.h \
    src/QProgressIndicator.h

FORMS += \
    forms/mainwindow.ui \
    forms/aboutdialog.ui \
    forms/settingswindow.ui

RESOURCES += \
    images/resource.qrc

##### PLATFORM SPECIFIC DEPLOYMENT #####
#--------------------------------------#
win32 {
    RC_FILE = ./images/app_logo/winIcon.rc
    LIBS += -L"C:/git/SeriesScraper/SeriesScraperApp/libraries" -llibeay32
}

macx {
    debug {
        #CONFIG -= app_bundle
    }
    QMAKE_MAC_SDK = macosx10.14
    ICON = $$PWD/images/app_logo/macIcon.icns

    QMAKE_POST_LINK += cd ~/Qt/5.12.3/;
    QMAKE_POST_LINK += ~/Qt/5.12.3/clang_64/bin/macdeployqt $$OUT_PWD/SeriesScraperApp.app;
    QMAKE_POST_LINK += cp -Rf $$PWD/../DeploymentFiles/general/* $$OUT_PWD/SeriesScraperApp.app/Contents/MacOs;
    QMAKE_POST_LINK += cp -Rf $$PWD/../DeploymentFiles/mac/Info.plist $$OUT_PWD/SeriesScraperApp.app/Contents;
}

unix:!macx {
    QMAKE_POST_LINK += cp -Rf $$PWD/../DeploymentFiles/general/* ./;
}
