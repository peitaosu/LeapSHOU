#-------------------------------------------------
#
# Project created by QtCreator 2015-05-28T13:56:25
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PalmAOOP
TEMPLATE = app


SOURCES += main.cpp \
    gesturerecognition.cpp \
    debug.cpp \
    vmouse.cpp

HEADERS  += \
    header/Leap.h \
    gesturerecognition.h \
    debug.h \
    header/fit.h \
    vmouse.h

FORMS    += \
    vmouse.ui

unix|win32: LIBS += -L$$PWD/lib/x64/ -lLeap

INCLUDEPATH += $$PWD/lib/x64
DEPENDPATH += $$PWD/lib/x64
