#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T18:26:56
#
#-------------------------------------------------

QT       += core gui
QT       += x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    vmouse.cpp

HEADERS  += widget.h \
    vmouse.h

FORMS    += widget.ui \
    vmouse.ui

LIBS += -lX11 -lXext -lXtst
