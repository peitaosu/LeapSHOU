#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T18:26:56
#
#-------------------------------------------------

QT       += core gui
#QT       += x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
    vmouse.cpp

HEADERS  += \
    vmouse.h

FORMS    += \
    vmouse.ui

#LIBS += -lX11 -lXext -lXtst
