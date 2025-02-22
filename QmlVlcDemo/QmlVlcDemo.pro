QT += qml quick multimedia

include(deps/QmlVlc/QmlVlc.pri)

INCLUDEPATH += deps

SOURCES += main.cpp

RESOURCES += main.qrc

OTHER_FILES += \
    skin/basic_2.qml \
    skin/pause.png \
    skin/play.png

CONFIG += c++11

macx {
    LIBS += -L/Applications/VLC.app/Contents/MacOS/lib
}

android {
    LIBS += -L$$PWD/android/libs/armeabi-v7a -lvlcjni

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

win32:{
  CONFIG(debug, debug|release) {
      BUILD_DIR=$$PWD/QmlVlcApp-win/Debug
  } else {
      BUILD_DIR=$$PWD/QmlVlcApp-win/Release
  }
}

win32:{
DESTDIR = $$BUILD_DIR
}
