TEMPLATE = app

QT += qml quick webengine
CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

win32:{
    ICON = CBox.ico
    QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01      #支持XP系统
}
