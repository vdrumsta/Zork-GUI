#-------------------------------------------------
#
# Project created by QtCreator 2017-10-04T13:34:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZorkLab3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Character.cpp \
    Command.cpp \
    CommandWords.cpp \
    Parser.cpp \
    Room.cpp \
    ZorkUL.cpp \
    keypressreceiver.cpp \
    item.cpp

HEADERS  += mainwindow.h \
    Character.h \
    Command.h \
    CommandWords.h \
    Parser.h \
    Room.h \
    ui_mainwindow.h \
    ZorkUL.h \
    keypressreceiver.h \
    item.h

FORMS    += mainwindow.ui

DISTFILES += \
    ZorkLab3.pro.user \
    Makefile \
    Makefile.Debug \
    Makefile.Release
