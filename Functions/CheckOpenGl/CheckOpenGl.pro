#-------------------------------------------------
#
# Project created by QtCreator 2018-09-19T15:26:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CheckOpenGl
TEMPLATE = app

CONFIG += c++11

CONFIG -= app_bundle
DESTDIR+=./

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
    glut.h

win32:{
#支持xp
QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
}
