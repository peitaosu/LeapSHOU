#include "eventcontrol.h"
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
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
     DP.show();
     DS.show();

     OP = new Operate(this);

     QTimer *EventTimer = new QTimer(this);
     connect(EventTimer,SIGNAL(timeout()),this,SLOT(EventListenner()));
     EventTimer->start(20);

     connect(this,SIGNAL(desktopS()),this,SLOT(desktop()));
     connect(this,SIGNAL(browserS()),this,SLOT(browser()));
     connect(this,SIGNAL(pcS()),this,SLOT(pc()));
     connect(this,SIGNAL(otherS()),this,SLOT(other()));

}

void EventControl::EventListenner(){
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
        break;
    case KEEP:
        break;
    case STOP:
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
        break;
    case KEEP:
        break;
    case STOP:
        emit pinchStop();
        break;
    default:
        break;
    }
    switch(GestureStatus[2]){
    case ON:
        break;
    case START:
        emit circleStart();
        break;
    case KEEP:
        emit circleKeep();
        break;
    case STOP:
        emit circleStop();
        break;
    default:
        break;
    }
    switch(GestureStatus[3]){
    case ON:
        break;
    case START:
        emit circleAntiStart();
        break;
    case KEEP:
        emit circleAntiKeep();
        break;
    case STOP:
        emit circleAntiStop();
        break;
    default:
        break;
    }
    switch(GR.gesHoldRight()){
    case 1:
        emit holdStart();
        break;
    case 2:
        emit holdKeep();
        break;
    case 3:
        emit holdDone();
        break;
    case 0:
        emit holdStop();
        break;
    default:
        break;
    }
    if(delay%500 == 0){
        switch(GR.gesHandDirection()){
        case 1:
            emit handLeft();
            break;
        case 2:
            emit handRight();
            break;
        case 3:
            emit handUp();
            break;
        case 4:
            emit handDown();
            break;
        case 5:
            emit handForward();
            break;
        case 6:
            emit handBackward();
            break;
        default:
            break;
        }
        delay++;
    }

}


void EventControl::desktop(){
    disconnect(this,SIGNAL(circleStart()),0,0);
    disconnect(this,SIGNAL(circleKeep()),0,0);
    disconnect(this,SIGNAL(circleStop()),0,0);
    disconnect(this,SIGNAL(circleAntiStart()),0,0);
    disconnect(this,SIGNAL(circleAntiKeep()),0,0);
    disconnect(this,SIGNAL(circleAntiStop()),0,0);
    disconnect(this,SIGNAL(pinchStart()),0,0);
    disconnect(this,SIGNAL(holdDone()),0,0);
    //disconnect(this,0,0,0);
    connect(this,SIGNAL(grabStart()),OP,SLOT(swipeWindow()));
    connect(this,SIGNAL(pinchStart()),this,SLOT(showDT()));
    connect(this,SIGNAL(pinchStop()),this,SLOT(hideDT()));
    connect(this,SIGNAL(turntableUp()),OP,SLOT(openFileManager()));

}
void EventControl::browser(){
    std::cout<<"BW"<<std::endl;
    //disconnect(this,0,0,0);
    disconnect(this,SIGNAL(circleStart()),0,0);
    disconnect(this,SIGNAL(circleKeep()),0,0);
    disconnect(this,SIGNAL(circleStop()),0,0);
    disconnect(this,SIGNAL(circleAntiStart()),0,0);
    disconnect(this,SIGNAL(circleAntiKeep()),0,0);
    disconnect(this,SIGNAL(circleAntiStop()),0,0);
    disconnect(this,SIGNAL(pinchStart()),0,0);
    disconnect(this,SIGNAL(holdDone()),0,0);

    connect(this,SIGNAL(circleStart()),OP,SLOT(MouseWheel()));
    connect(this,SIGNAL(circleKeep()),OP,SLOT(MouseWheel()));
    connect(this,SIGNAL(circleStop()),OP,SLOT(MouseWheelStop()));
    connect(this,SIGNAL(circleAntiStart()),OP,SLOT(MouseWheelN()));
    connect(this,SIGNAL(circleAntiKeep()),OP,SLOT(MouseWheelN()));
    connect(this,SIGNAL(circleAntiStop()),OP,SLOT(MouseWheelStop()));
    connect(this,SIGNAL(pinchStart()),OP,SLOT(swipeBrowserTab()));
    //connect(this,SIGNAL(grabStart()),OP,SLOT(swipeWindow()));
    connect(this,SIGNAL(holdDone()),this,SLOT(MouseLeftClick()));

}
void EventControl::pc(){
    //disconnect(this,0,0,0);
    disconnect(this,SIGNAL(circleStart()),0,0);
    disconnect(this,SIGNAL(circleKeep()),0,0);
    disconnect(this,SIGNAL(circleStop()),0,0);
    disconnect(this,SIGNAL(circleAntiStart()),0,0);
    disconnect(this,SIGNAL(circleAntiKeep()),0,0);
    disconnect(this,SIGNAL(circleAntiStop()),0,0);
    disconnect(this,SIGNAL(pinchStart()),0,0);
    disconnect(this,SIGNAL(holdDone()),0,0);
    connect(this,SIGNAL(grabStart()),OP,SLOT(swipeWindow()));
}
void EventControl::other(){
    //disconnect(this,0,0,0);
    disconnect(this,SIGNAL(circleStart()),0,0);
    disconnect(this,SIGNAL(circleKeep()),0,0);
    disconnect(this,SIGNAL(circleStop()),0,0);
    disconnect(this,SIGNAL(circleAntiStart()),0,0);
    disconnect(this,SIGNAL(circleAntiKeep()),0,0);
    disconnect(this,SIGNAL(circleAntiStop()),0,0);
    disconnect(this,SIGNAL(pinchStart()),0,0);
    disconnect(this,SIGNAL(holdDone()),0,0);
    connect(this,SIGNAL(circleStart()),OP,SLOT(swipeWindow()));
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
    DT.showDisplayTurntable(DT_x,DT_y);
}

void EventControl::hideDT(){
    Leap::InteractionBox iBox = controller.frame().interactionBox();
    int DT_x = iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).x * QApplication::desktop()->width() -160;
    int DT_y = (1-iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).y) * QApplication::desktop()->height() -160;
    if(Turntable[0] != 0){
        float slope = (DT_y - Turntable[1])/(DT_x - Turntable[0]);
        int Horizontal,Vertical;
        if(DT_x - Turntable[0] >= 0){
            Horizontal = 1;
        }else{
            Horizontal = -1;
        }
        if(DT_y - Turntable[1] >= 0){
            Vertical = 1;
        }else{
            Vertical = -1;
        }

        if(slope >= 1 || slope <= -1){
            if(Vertical = 1){
                emit turntableUp();
            }else if(Vertical = -1){
                emit turntableDown();
            }
        }else{
            if(Horizontal = 1){
                emit turntableRight();
            }else if(Horizontal = -1){
                emit turntableLeft();
            }
        }
    }
    DT.hide();
}

