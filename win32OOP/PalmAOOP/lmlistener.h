#ifndef LMLISTENER_H
#define LMLISTENER_H
#include "header/Leap.h"
#include "vmouse.h"
using namespace Leap;
class LMListener : public Listener
{
public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    enum GSTATE{GSTART=1,GCONTINUE=2,GSTOP=0};


    float getHandCenterX(const Controller &);
    float getHandCenterY(const Controller &);
    float getHandCenterZ(const Controller &);

    friend class VMouse;
private:
    Leap::Vector handCenter;

    float handCenter_x;
    float handCenter_y;
    float handCenter_z;
    GSTATE GGrab;
    GSTATE GCircle;
    GSTATE GDirection;
    GSTATE GHold;


};

#endif // LMLISTENER_H
