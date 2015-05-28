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


SOURCES += main.cpp\
        gestureshow.cpp \
    vmouse.cpp \
    lmlistener.cpp \
    control.cpp \
    fgwinlistener.cpp

HEADERS  += gestureshow.h \
    header/Leap.h \
    vmouse.h \
    lmlistener.h \
    control.h \
    fgwinlistener.h

FORMS    += gestureshow.ui

unix|win32: LIBS += -L$$PWD/lib/x64/ -lLeap

INCLUDEPATH += $$PWD/lib/x64
DEPENDPATH += $$PWD/lib/x64
