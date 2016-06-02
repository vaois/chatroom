#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T17:02:37
#
#-------------------------------------------------

QT       += core gui
QT       +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = threadchat
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    server.cpp \
    thread.cpp \
    protocol.cpp \
    tcpclientsocket.cpp

HEADERS  += dialog.h \
    server.h \
    thread.h \
    protocol.h \
    tcpclientsocket.h

FORMS    += dialog.ui
