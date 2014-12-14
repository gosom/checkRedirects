#-------------------------------------------------
#
# Project created by QtCreator 2014-12-13T19:03:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = checkRedirect
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myurl.cpp \
    crawler.cpp \
    request.cpp

HEADERS  += mainwindow.h \
    myurl.h \
    crawler.h \
    request.h

FORMS    += mainwindow.ui

QT += network

QMAKE_CXXFLAGS += -std=c++11
