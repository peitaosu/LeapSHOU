#include "operate.h"
#include <QDesktopServices>
#include <QUrl>
#include <Windows.h>
#include <iostream>
Operate::Operate(QObject *parent) :
    QObject(parent)
{
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,65535,40000,0,0);
}

void Operate::MouseLeftClick(int x,int y){
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,x,y,0,0);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0, 0, 0 );
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,65535,40000,0,0);
}
void Operate::MouseLeftDClick(int x,int y){
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,x,y,0,0);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0, 0, 0 );
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0, 0, 0 );
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,65535,40000,0,0);
}
void Operate::MouseRightClick(int x,int y){
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,x,y,0,0);
    mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP,0,0, 0, 0 );
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,65535,40000,0,0);
}
void Operate::MouseWheel(){
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 5, 0);
}
void Operate::MouseWheelN(){
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -5, 0);
}
void Operate::MouseWheel(int w){
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, w, 0);
}
void Operate::MouseWheelStop(){
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 0, 0);
}

void Operate::showDesktop(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(0x44,0,0,0);
    keybd_event(0x44,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

void Operate::openFileManager(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(0x45,0,0,0);
    keybd_event(0x45,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

void Operate::swipeWindow(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(VK_TAB,0,0,0);
    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_TAB,0,0,0);
    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

void Operate::swipeWindow(int x){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(VK_TAB,0,0,0);
    for(int i=0;i<x;i++){
        keybd_event(VK_TAB,0,0,0);
        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
    }
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

void Operate::swipeBrowserTab(){
    keybd_event(VK_CONTROL,0,0,0);
    keybd_event(VK_TAB,0,0,0);
    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
}
void Operate::moveWindowtoLeft(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(VK_LEFT,0,0,0);
    keybd_event(VK_LEFT,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}
void Operate::moveWindowtoRight(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(VK_RIGHT,0,0,0);
    keybd_event(VK_RIGHT,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}
void Operate::moveWindowtoUp(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(VK_UP,0,0,0);
    keybd_event(VK_UP,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}
void Operate::moveWindowtoDown(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(VK_DOWN,0,0,0);
    keybd_event(VK_DOWN,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

void Operate::openBrowser(){
    QUrl url("http://www.shou.edu.cn");
    QDesktopServices::openUrl(url);
}

void Operate::goEnter(){
    keybd_event(VK_RETURN,0,0,0);
    keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);
}

void Operate::goBack(){
    keybd_event(VK_BACK,0,0,0);
    keybd_event(VK_BACK,0,KEYEVENTF_KEYUP,0);
}

void Operate::goRefresh(){
    keybd_event(VK_F5,0,0,0);
    keybd_event(VK_F5,0,KEYEVENTF_KEYUP,0);
}
