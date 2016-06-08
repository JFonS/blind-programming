#-------------------------------------------------
#
# Project created by QtCreator 2016-06-03T18:41:29
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        serverthread.cpp\
server.cpp

HEADERS  += mainwindow.h\
        server.h\
        serverthread.h

FORMS    += mainwindow.ui
