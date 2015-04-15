#-------------------------------------------------
#
# Project created by QtCreator 2015-04-09T13:36:12
#
#-------------------------------------------------

QT       += core gui
QT       += x11extras
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PalmA
TEMPLATE = app


SOURCES += main.cpp\
        geswin.cpp \
    data.cpp \
    vmouse.cpp \
    ctrl.cpp

HEADERS  += geswin.h\
    header/LeapMath.h \
    header/Leap.h \
    data.h \
    vmouse.h \
    header/fit.h \
    ctrl.h \
    geslist.h

FORMS    += geswin.ui \
    vmouse.ui \
    ctrl.ui

LIBS += -lX11 -lXext -lXtst
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/x64/release/ -lLeap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/x64/debug/ -lLeap
else:unix: LIBS += -L$$PWD/lib/x64/ -lLeap

INCLUDEPATH += $$PWD/lib/x64
DEPENDPATH += $$PWD/lib/x64
