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
//#include "displaystatus.h"
#include "displayturntable.h"
#include "displaymouseline.h"
#include "drawgesture.h"
#include "roadmapgesture.h"
#include "settingpanel.h"
class EventControl : public QObject
{
    Q_OBJECT
public:
    explicit EventControl(QObject *parent = 0);
    ~EventControl();
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

    void handLeft();
    void handRight();
    void handUp();
    void handDown();
    void handForward();
    void handBackward();


    void desktopS();
    void browserS();
    void pcS();
    void otherS();

    void turntableUp();
    void turntableDown();
    void turntableLeft();
    void turntableRight();

    void disconnectAllS();

    void showGesture(int);

    void showRoadMapS();

    void RoadMapS(int,int,int,int);
public slots:
    void EventListenner();


    void desktop();
    void browser();
    void pc();
    void other();

    void MouseLeftClick();
    void MouseLeftDClick();

    void showDT();
    void hideDT();

    void disconnectAll();

    void showRoadMap();
    void outRoadMap(int*);
    void RoadMap(int,int,int,int);
private:

    Leap::Controller controller;
    LMListenner listenner;
    GestureRecognition GR;
    FGWin FGW;
    VMouse VM;
    Operate *OP;
    Display DP;
    //DisplayStatus DS;
    DisplayTurntable DT;
    DisplayMouseLine DML;
    //DrawGesture DG;
    RoadMapGesture *RMG;
    SettingPanel *SP;
};

extern int Turntable[2];

#endif // EVENTCONTROL_H
