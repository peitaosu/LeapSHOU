#include "eventcontrol.h"
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>

#define GRABSTART_SHOW 111
#define GRABKEEP_SHOW 112
#define GRABSTOP_SHOW 110
#define PINCHSTART_SHOW 121
#define PINCHKEEP_SHOW 122
#define PINCHSTOP_SHOW 120
#define HOLDSTART_SHOW 131
#define HOLDKEEP_SHOW 132
#define HOLDDONE_SHOW 133
#define HOLDSTOP_SHOW 130
#define CIRCLESTART_SHOW 141
#define CIRCLEKEEP_SHOW 142
#define CIRCLESTOP_SHOW 140
#define CIRCLEANTISTART_SHOW 151
#define CIRCLEANTIKEEP_SHOW 152
#define CIRCLEANTISTOP_SHOW 150



#define ON 0
#define START 1
#define KEEP 2
#define STOP 3
#define ANTI 4

#define GESMAX 4

int GestureStatus[GESMAX] = {0};
bool GestureStatusPrev[GESMAX] = {0};
bool GestureStatusCrt[GESMAX] ={0};
int FGWPrev = -1;
int delay = 0;
int Turntable[2] = {0};
EventControl::EventControl(QObject *parent) :
    QObject(parent)
{
     controller.addListener(listenner);
     controller.setPolicyFlags(Leap::Controller::PolicyFlag::POLICY_BACKGROUND_FRAMES);
     VM.show();
//     DP = new Display();
     DP.show();
     //DS.show();
     DML.show();
     OP = new Operate(this);

     QTimer *EventTimer = new QTimer(this);
     connect(EventTimer,SIGNAL(timeout()),this,SLOT(EventListenner()));
     EventTimer->start(20);

     connect(this,SIGNAL(showGesture(int)),&DP,SLOT(showGesture(int)));

     connect(this,SIGNAL(desktopS()),this,SLOT(desktop()));
     connect(this,SIGNAL(browserS()),this,SLOT(browser()));
     connect(this,SIGNAL(pcS()),this,SLOT(pc()));
     connect(this,SIGNAL(otherS()),this,SLOT(other()));

     connect(this,SIGNAL(disconnectAllS()),this,SLOT(disconnectAll()));

     connect(this,SIGNAL(handUp()),OP,SLOT(moveWindowtoUp()));
     connect(this,SIGNAL(handDown()),OP,SLOT(moveWindowtoDown()));
     connect(this,SIGNAL(handLeft()),OP,SLOT(moveWindowtoLeft()));
     connect(this,SIGNAL(handRight()),OP,SLOT(moveWindowtoRight()));
}

EventControl::~EventControl(){
    controller.removeListener(listenner);
}

void EventControl::EventListenner(){
    if(Turntable[0] != 0){
        DML.setLine(Turntable[0],Turntable[1],GR.getX(),GR.getY());
    }else{
        DML.setLine(0,0,0,0);
    }
    //std::cout<<FGW.getFGWinName()<<std::endl;

    if(FGW.getFGWinName() != FGWPrev){
        switch(FGW.getFGWinName()){
        case 1:
            emit desktopS();
            break;
        case 2:
            emit browserS();
            break;
        case 3:
            emit pcS();
            break;
        case 0:
            emit otherS();
            break;
        default:
            break;
        }
        FGWPrev = FGW.getFGWinName();
    }

    for(int i = 0;i<GESMAX;i++){
        GestureStatusPrev[i] = GestureStatusCrt[i];
    }

    GestureStatusCrt[0] = GR.gesGrabRight();
    GestureStatusCrt[1] = GR.gesPinchRight();
    GestureStatusCrt[2] = GR.gesCircle();
    GestureStatusCrt[3] = GR.gesCircleAnti();

    for(int i = 0;i<GESMAX;i++){
        if(!GestureStatusPrev[i] && !GestureStatusCrt[i]){
            //00
            GestureStatus[i] = ON;
        }else if(!GestureStatusPrev[i] && GestureStatusCrt[i]){
            //01
            GestureStatus[i] = START;
        }else if(GestureStatusPrev[i] && GestureStatusCrt[i]){
            //11
            GestureStatus[i] = KEEP;
        }else if(GestureStatusPrev[i] && !GestureStatusCrt[i]){
            //10
            GestureStatus[i] = STOP;
        }
    }

    //
    switch(GestureStatus[0]){
    case ON:
        break;
    case START:
        emit grabStart();
        emit showGesture(GRABSTART_SHOW);
        break;
    case KEEP:
        emit showGesture(GRABKEEP_SHOW);
        break;
    case STOP:
        emit showGesture(GRABSTOP_SHOW);
        emit grabStop();
        break;
    default:
        break;
    }
    switch(GestureStatus[1]){
    case ON:
        break;
    case START:
        emit pinchStart();
        emit showGesture(PINCHSTART_SHOW);
        break;
    case KEEP:
        emit showGesture(PINCHKEEP_SHOW);
        break;
    case STOP:
        emit pinchStop();
        emit showGesture(PINCHSTOP_SHOW);
        break;
    default:
        break;
    }
    switch(GestureStatus[2]){
    case ON:
        break;
    case START:
        emit circleStart();
        emit showGesture(CIRCLESTART_SHOW);
        break;
    case KEEP:
        emit circleKeep();
        emit showGesture(CIRCLEKEEP_SHOW);
        break;
    case STOP:
        emit circleStop();
        emit showGesture(CIRCLESTOP_SHOW);
        break;
    default:
        break;
    }
    switch(GestureStatus[3]){
    case ON:
        break;
    case START:
        emit circleAntiStart();
        emit showGesture(CIRCLEANTISTART_SHOW);
        break;
    case KEEP:
        emit circleAntiKeep();
        emit showGesture(CIRCLEANTIKEEP_SHOW);
        break;
    case STOP:
        emit circleAntiStop();
        emit showGesture(CIRCLEANTISTOP_SHOW);
        break;
    default:
        break;
    }
    switch(GR.gesHoldRight()){
    case 1:
        emit holdStart();
        emit showGesture(HOLDSTART_SHOW);
        break;
    case 2:
        emit holdKeep();
        emit showGesture(HOLDKEEP_SHOW);
        break;
    case 3:
        emit holdDone();
        emit showGesture(HOLDDONE_SHOW);
        break;
    case 4:
        emit holdStop();
        emit showGesture(HOLDSTOP_SHOW);
        break;
    case 0:
        break;
    default:
        break;
    }
    if(delay%10 == 0){
        //std::cout<<GR.gesHandDirection()<<std::endl;
        switch(GR.gesHandDirection()){
        case 1:
            emit handLeft();
            std::cout<<"LEFT"<<std::endl;
            break;
        case 2:
            emit handRight();
            std::cout<<"RIGHT"<<std::endl;
            break;
        case 3:
            emit handUp();
            std::cout<<"UP"<<std::endl;
            break;
        case 4:
            emit handDown();
            std::cout<<"DOWN"<<std::endl;
            break;
        case 5:
            emit handForward();
            std::cout<<"FWARD"<<std::endl;
            break;
        case 6:
            emit handBackward();
            std::cout<<"BWARD"<<std::endl;
            break;
        default:
            break;
        }

    }
    delay++;

}


void EventControl::desktop(){
    emit disconnectAllS();
    connect(this,SIGNAL(grabStart()),OP,SLOT(swipeWindow()));
    connect(this,SIGNAL(pinchStart()),this,SLOT(showDT()));
    connect(this,SIGNAL(pinchStart()),this,SLOT(MouseLeftClick()));
    connect(this,SIGNAL(pinchStop()),this,SLOT(hideDT()));
    connect(this,SIGNAL(turntableUp()),OP,SLOT(openFileManager()));
    connect(this,SIGNAL(turntableDown()),OP,SLOT(openBrowser()));
    connect(this,SIGNAL(turntableLeft()),OP,SLOT(openBrowser()));
    connect(this,SIGNAL(turntableRight()),OP,SLOT(openFileManager()));

}
void EventControl::browser(){
    emit disconnectAllS();
    connect(this,SIGNAL(circleStart()),OP,SLOT(MouseWheel()));
    connect(this,SIGNAL(circleKeep()),OP,SLOT(MouseWheel()));
    connect(this,SIGNAL(circleStop()),OP,SLOT(MouseWheelStop()));
    connect(this,SIGNAL(circleAntiStart()),OP,SLOT(MouseWheelN()));
    connect(this,SIGNAL(circleAntiKeep()),OP,SLOT(MouseWheelN()));
    connect(this,SIGNAL(circleAntiStop()),OP,SLOT(MouseWheelStop()));
    connect(this,SIGNAL(pinchStart()),OP,SLOT(swipeBrowserTab()));
    connect(this,SIGNAL(holdDone()),this,SLOT(MouseLeftClick()));
    connect(this,SIGNAL(grabStart()),OP,SLOT(goBack()));

}
void EventControl::pc(){
    emit disconnectAllS();
    connect(this,SIGNAL(circleStart()),OP,SLOT(MouseWheel()));
    connect(this,SIGNAL(circleKeep()),OP,SLOT(MouseWheel()));
    connect(this,SIGNAL(circleStop()),OP,SLOT(MouseWheelStop()));
    connect(this,SIGNAL(circleAntiStart()),OP,SLOT(MouseWheelN()));
    connect(this,SIGNAL(circleAntiKeep()),OP,SLOT(MouseWheelN()));
    connect(this,SIGNAL(circleAntiStop()),OP,SLOT(MouseWheelStop()));
    connect(this,SIGNAL(pinchStart()),this,SLOT(showDT()));
    connect(this,SIGNAL(pinchStart()),this,SLOT(MouseLeftClick()));
    connect(this,SIGNAL(pinchStop()),this,SLOT(hideDT()));
    connect(this,SIGNAL(turntableUp()),OP,SLOT(goEnter()));
    connect(this,SIGNAL(turntableDown()),OP,SLOT(goBack()));
    connect(this,SIGNAL(turntableLeft()),OP,SLOT(goRefresh()));
    connect(this,SIGNAL(turntableRight()),OP,SLOT(showDesktop()));

}
void EventControl::other(){
    emit disconnectAllS();
}

void EventControl::disconnectAll(){
    disconnect(this,SIGNAL(circleStart()),0,0);
    disconnect(this,SIGNAL(circleKeep()),0,0);
    disconnect(this,SIGNAL(circleStop()),0,0);
    disconnect(this,SIGNAL(circleAntiStart()),0,0);
    disconnect(this,SIGNAL(circleAntiKeep()),0,0);
    disconnect(this,SIGNAL(circleAntiStop()),0,0);
    disconnect(this,SIGNAL(pinchStart()),0,0);
    disconnect(this,SIGNAL(pinchStop()),0,0);
    disconnect(this,SIGNAL(grabStart()),0,0);
    disconnect(this,SIGNAL(grabStop()),0,0);
    disconnect(this,SIGNAL(holdDone()),0,0);
    disconnect(this,SIGNAL(turntableUp()),0,0);
    disconnect(this,SIGNAL(turntableDown()),0,0);
    disconnect(this,SIGNAL(turntableLeft()),0,0);
    disconnect(this,SIGNAL(turntableRight()),0,0);

}

void EventControl::MouseLeftClick(){
    Leap::InteractionBox iBox = controller.frame().interactionBox();
    int mouse_x = iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).x * 65535;
    int mouse_y = (1-iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).y) * 65535;

    OP->MouseLeftClick(mouse_x,mouse_y);
}

void EventControl::MouseLeftDClick(){
    Leap::InteractionBox iBox = controller.frame().interactionBox();
    int mouse_x = iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).x * 65535;
    int mouse_y = (1-iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).y) * 65535;

    OP->MouseLeftDClick(mouse_x,mouse_y);
}

void EventControl::showDT(){
    Leap::InteractionBox iBox = controller.frame().interactionBox();
    int DT_x = iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).x * QApplication::desktop()->width() -160;
    int DT_y = (1-iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).y) * QApplication::desktop()->height() -160;
    Turntable[0] = DT_x;
    Turntable[1] = DT_y;
    std::cout<<FGW.getFGWinName()<<std::endl;
    switch (FGW.getFGWinName()) {
    case 1:
        DT.setFGWin(1);
        DT.showDisplayTurntable(DT_x,DT_y);
        break;
    case 2:
         //DT.showDisplayTurntable(DT_x,DT_y,2);
         break;
    case 3:
        DT.setFGWin(3);
         DT.showDisplayTurntable(DT_x,DT_y);
         break;
    default:
        break;
    }

}

void EventControl::hideDT(){
    Leap::InteractionBox iBox = controller.frame().interactionBox();
    int DT_x = iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).x * QApplication::desktop()->width() -160;
    int DT_y = (1-iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).y) * QApplication::desktop()->height() -160;
    if(Turntable[0] != 0){
        float slope = (DT_y - Turntable[1])/(DT_x - Turntable[0]);
        int Horizontal,Vertical=0;
        if(DT_x - Turntable[0] >= 0){
            Horizontal = 1;
        }else{
            Horizontal = -1;
        }
        if(DT_y - Turntable[1] >= 0){
            Vertical = -1;
        }else{
            Vertical = 1;
        }
        Turntable[0] = 0;
        Turntable[1] = 0;
        if(slope >= 1 || slope <= -1){
            if(Vertical == 1){
                emit turntableUp();
            }else if(Vertical == -1){
                emit turntableDown();
            }
        }else{
            if(Horizontal == 1){
                emit turntableRight();
            }else if(Horizontal == -1){
                emit turntableLeft();
            }
        }
    }
    DT.hide();
}

