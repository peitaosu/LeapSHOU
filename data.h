#ifndef DATA
#define DATA

#include <iostream>
#include "header/Leap.h"
#include "header/fit.h"
using namespace Leap;

class NewListener:public Listener{
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
private:

};

extern int Status;
extern int gesStatus;
extern int mouse_x;
extern int mouse_y;
extern int screen_x;
extern int screen_y;
extern int UserDeviceScreenWidth;
extern int UserDeviceScreenHeight;
extern int PosXM,PosYM;
extern double PosSlope;
extern int HoldPtr[2];
#endif // DATA

