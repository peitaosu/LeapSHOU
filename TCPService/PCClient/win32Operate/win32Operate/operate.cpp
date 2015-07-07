#include "operate.h"
#include <Windows.h>
#include <iostream>
#pragma comment(lib,"User32.lib")
Operate::Operate(QObject *parent) :
    QObject(parent)
{

}

void Operate::sendUp(){
    std::cout<<"sendUp"<<std::endl;
    keybd_event(VK_UP,0,0,0);
    keybd_event(VK_UP,0,KEYEVENTF_KEYUP,0);
}
void Operate::sendDown(){
    std::cout<<"sendDown"<<std::endl;
    keybd_event(VK_DOWN,0,0,0);
    keybd_event(VK_DOWN,0,KEYEVENTF_KEYUP,0);
}
