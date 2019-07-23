QT += core
QT -= gui

CONFIG += c++11

TARGET = QuaZIPDemo
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp


INCLUDEPATH += $$PWD/QuaZip-dll_build/include
CONFIG(debug, debug|release){
    LIBS += -L$$PWD/QuaZip-dll_build/lib/debug -lquazipd
} else {
    LIBS += -L$$PWD/QuaZip-dll_build/lib/release -lquazip
}

