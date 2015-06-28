#ifndef LMLISTENNER_H
#define LMLISTENNER_H
#include <iostream>
#include "header/Leap.h"
#include "displaystatus.h"
class LMListenner:public Leap::Listener
{
public:
    virtual void onInit(const Leap::Controller&);
    virtual void onConnect(const Leap::Controller&);
    virtual void onDisconnect(const Leap::Controller&);
    virtual void onServiceConnect(const Leap::Controller&);
    virtual void onServiceDisconnect(const Leap::Controller&);
    virtual void onExit(const Leap::Controller&);
    virtual void onFrame(const Leap::Controller&);
    virtual void onFocusGained(const Leap::Controller&);
    virtual void onFocusLost(const Leap::Controller&);
    virtual void onDeviceChange(const Leap::Controller&);
private:
};

extern int Status[3];

#endif // LMLISTENNER_H
