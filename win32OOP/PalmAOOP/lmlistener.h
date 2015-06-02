#ifndef LMLISTENER_H
#define LMLISTENER_H
#include "header/Leap.h"
#include "vmouse.h"
using namespace Leap;
class LMListener : public QObject,public Listener
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
    void getFrameID(const Controller&);
    void getVector(const Controller&);

    friend class VMouse;
private:
    Vector handCenter;
    GSTATE GGrab;
    GSTATE GCircle;
    GSTATE GDirection;
    GSTATE GHold;
    


};

#endif // LMLISTENER_H
