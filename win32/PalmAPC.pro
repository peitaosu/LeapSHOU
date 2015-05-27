#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T15:03:00
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PalmAPC
TEMPLATE = app


SOURCES += main.cpp\
    data.cpp \
    vmouse.cpp \
    getinfo.cpp \
    sysctrl.cpp

HEADERS  += \
    header/Leap.h \
    data.h \
    header/fit.h \
    vmouse.h \
    getinfo.h \
    sysctrl.h

FORMS    += \
    vmouse.ui

unix|win32: LIBS += -L$$PWD/lib/x64/ -lLeap

INCLUDEPATH += $$PWD/lib/x64
DEPENDPATH += $$PWD/lib/x64
