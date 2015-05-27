#include "sysctrl.h"
#include <QTimer>
#include <Windows.h>
#include "data.h"
#include "getinfo.h"
SysCtrl::SysCtrl(){
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,65535,40000,0,0);

    QTimer *SysCtrlTimer = new QTimer(this);
    connect(SysCtrlTimer,SIGNAL(timeout()),this,SLOT(SendWM()));
    SysCtrlTimer->start(20);
}

SysCtrl::~SysCtrl(){

}

void SysCtrl::SendWM(){
    switch(gesStatus){
    //CLK
    case 31:
    {
        if(BW_CLKWS){
            mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -5, 0);
        }
        break;
    }
    case 32:{
        if(BW_ATCLKWS){
            mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 5, 0);
        }
        //break;
    }
    case 30:{
        if(BW_CLKWS || BW_ATCLKWS){
            mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 0, 0);
        }
        //break;
    }

    //One Hand Grab
        case 131:{
        if(BW_TAB){
            keybd_event(17,0,0,0);
            keybd_event(9,0,0,0);
            std::cout<<"GRAB!!!!"<<std::endl;
            keybd_event(9,0,KEYEVENTF_KEYUP,0);
            keybd_event(17,0,KEYEVENTF_KEYUP,0);
            break;
        }
        case 130:{
            }
            break;
        }
        //TWO Hand Grab
        case 1311:{
            //if(){

            //}
            break;
        }
        case 1310:{
            //if(){

            //}
            break;
        }

    //One Hand Pinch
    case 111:{
        std::cout<<"CLICK"<<std::endl;
        if(BW_LINK){
            mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,mouse_x,mouse_y,0,0);
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0, 0, 0 );
            mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,65535,40000,0,0);
        }
        break;
    }
    case 110:{
        if(BW_LINK){
            //mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
        }
        //break;
    }
    //TWO Hand Pinch
    case 1111:{
        //if(){

        //}
        break;
    }
    case 1110:{
        //if(){

        //}
        break;
    }


    }

}
