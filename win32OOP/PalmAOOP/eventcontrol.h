#ifndef EVENTCONTROL_H
#define EVENTCONTROL_H

#include <QObject>
#include "header/Leap.h"
#include "lmlistenner.h"
#include "gesturerecognition.h"
#include "fgwin.h"
#include "operate.h"
#include "vmouse.h"
#include "display.h"
#include "displaystatus.h"
#include "displayturntable.h"

class EventControl : public QObject
{
    Q_OBJECT
public:
    explicit EventControl(QObject *parent = 0);

signals:
    void grabStart();
    void grabStop();
    void pinchStart();
    void pinchStop();
    void holdStart();
    void holdKeep();
    void holdDone();
    void holdStop();
    void circleStart();
    void circleKeep();
    void circleStop();
    void circleAntiStart();
    void circleAntiKeep();
    void circleAntiStop();

    void desktopS();
    void browserS();
    void pcS();
    void otherS();

public slots:
    void EventListenner();


    void desktop();
    void browser();
    void pc();
    void other();

    void MouseLeftClick();
    void MouseLeftDClick();
private:

    Leap::Controller controller;
    LMListenner listenner;
    GestureRecognition GR;
    FGWin FGW;
    VMouse VM;
    Operate *OP;
    Display DP;
    DisplayStatus DS;
    DisplayTurntable DT;

};


#endif // EVENTCONTROL_H
