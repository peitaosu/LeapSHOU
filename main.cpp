/***********************************************************************\
* Copyright (C) 2014-2015 Shanghai Ocean University. All rights reserved.                         *
* This is a Human-Computer Interaction System based on LEAP MOTION CONTROLLER. *
* The system can be applied on different platforms, such as Windows, Linux and Mac,    *
* programmed in C/C+, combined with Qt. It contains System API, TCP/IP, Digital Picture*
* Processing Technique and Embedded Developing and can be applied in AR/VR, Robots*
* and the Internet of things.                                                                           --TONY SU          *
\************************************************************************/

#include "geswin.h"
#include "vmouse.h"
#include <QApplication>
#include "data.h"
#include "ctrl.h"
int main(int argc, char *argv[])
{
    NewListener listener;
    Controller controller;
    controller.addListener(listener);
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
    controller.config().save();

    QApplication a(argc, argv);
    GesWin w;
    w.show();
    ctrl c;
    c.show();
    vmouse v;
    v.show();


    return a.exec();
}
