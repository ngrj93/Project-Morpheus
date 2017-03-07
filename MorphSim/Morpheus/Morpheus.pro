#-------------------------------------------------
#
# Project created by QtCreator 2016-02-13T23:54:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Morpheus
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spinboxc.cpp \
    horizontalsliderc.cpp \
    pushbuttonc.cpp \
    worker.cpp

HEADERS  += mainwindow.h \
    spinboxc.h \
    horizontalsliderc.h \
    pushbuttonc.h \
    globshare.h \
    worker.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11

LIBS += \
       -lboost_system\

QMAKE_CXXFLAGS += -std=gnu++0x -pthread
LIBS += -pthread
LIBS += -lrt
