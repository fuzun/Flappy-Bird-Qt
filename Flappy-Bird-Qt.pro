# Flappy Bird Qt
# github.com/fuzun/flappy-bird-qt

QT += core gui opengl multimedia
QT -= network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Flappy-Bird-Qt
TEMPLATE = app

VERSION = 1.0.0

DEFINES += QT_DEPRECATED_WARNINGS

win32:RC_ICONS += assets/icon.ico

SOURCES += \
    source/MainWindow.cpp \
    source/Bird.cpp \
    source/Button.cpp \
    source/Game.cpp \
    source/Physics.cpp \
    source/Scene.cpp \
    source/main.cpp \
    source/Sound.cpp \
    source/View.cpp \
    source/StrobeDialog.cpp

HEADERS += \
    source/MainWindow.h \
    source/Bird.h \
    source/Button.h \
    source/Game.h \
    source/Physics.h \
    source/Scene.h \
    source/common.h \
    source/Sound.h \
    source/View.h \
    source/StrobeDialog.h

RESOURCES += \
    assets/Resource.qrc

# strobe-api :

SOURCES += \
    source/strobe-api/strobe/strobe-api.cpp \
    source/strobe-api/strobe/strobe-core.cpp

HEADERS += \
    source/strobe-api/strobe/strobe-api.h \
    source/strobe-api/strobe/strobe-core.h
