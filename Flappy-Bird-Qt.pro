# Flappy Bird Qt
# github.com/fuzun/flappy-bird-qt

QT += core gui opengl multimedia
QT -= network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Flappy-Bird-Qt
TEMPLATE = app

VERSION = 1.5.2

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/source

INCLUDEPATH += \ # submodules
               $$PWD/source/tiny-dnn \
               $$PWD/source/strobe-api/strobe

win32:RC_ICONS += assets/icon.ico

CONFIG += c++14

SOURCES += \
    source/MainWindow/MainWindow.cpp \
    source/Bird/Bird.cpp \
    source/Button/Button.cpp \
    source/Game/Game.cpp \
    source/Physics/Physics.cpp \
    source/Scene/Scene.cpp \
    source/main.cpp \
    source/Sound/Sound.cpp \
    source/View/View.cpp \
    source/StrobeDialog/StrobeDialog.cpp \
    source/AI/AI.cpp

HEADERS += \
    source/MainWindow/MainWindow.h \
    source/Bird/Bird.h \
    source/Button/Button.h \
    source/Game/Game.h \
    source/Physics/Physics.h \
    source/Scene/Scene.h \
    source/common.h \
    source/Sound/Sound.h \
    source/View/View.h \
    source/StrobeDialog/StrobeDialog.h \
    source/AI/AI.h \
    source/vector.h

RESOURCES += \
    assets/Resource.qrc

