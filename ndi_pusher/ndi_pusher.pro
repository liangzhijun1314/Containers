#-------------------------------------------------
#
# Project created by QtCreator 2019-11-28T10:57:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ndi_pusher
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_FILE += ndi_pusher.rc
MOC_DIR=temp/.moc
RCC_DIR=temp/.rcc
UI_DIR=temp/.ui
OBJECTS_DIR=temp/.obj
CONFIG += warn_off
win32:{
  CONFIG(debug, debug|release) {
      BUILD_DIR=$$PWD/build-ndi_pusher/Debug
  } else {
      BUILD_DIR=$$PWD/build-ndi_pusher/Release
  }
}
win32:{
DESTDIR = $$BUILD_DIR
}

include(./IPAddressEdit/IPAddressEdit.pri)
SOURCES += \
        main.cpp \
    infodialog.cpp \
    titlebar.cpp \
    centerwidget.cpp \
    ndipusher.cpp

HEADERS += \
    infodialog.h \
    commonhelper.h \
    titlebar.h \
    centerwidget.h \
    ndipusher.h

RESOURCES += \
    ndi_pusher.qrc

QSLOG_INCLUDE_PATH=$$PWD/thirdparty/QsLog/include
INCLUDEPATH += $$QSLOG_INCLUDE_PATH  \

LIBS += -L$$PWD/thirdparty/QsLog/lib/
win32 {
    CONFIG(debug, debug|release) {
        LIBS += -L$$PWD/thirdparty/QsLog/lib/x64/Debug
    } else {
        LIBS += -L$$PWD/thirdparty/QsLog/lib/x64/Release
    }
    LIBS += -lQsLog2
}
