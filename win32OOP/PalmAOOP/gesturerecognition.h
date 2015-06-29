#ifndef GESTURERECOGNITION_H
#define GESTURERECOGNITION_H

#include"header/Leap.h"
#include"header/fit.h"
class GestureRecognition
{
public:
    GestureRecognition();

    float getSlope(int);
    float getX();
    float getY();
    float getZ();
    float getFPS();

    int gesHoldLeft();
    int gesHoldRight();
    int gesHoldDouble();
    bool gesPinchLeft();
    bool gesPinchRight();
    bool gesPinchDouble();
    bool gesGrabLeft();
    bool gesGrabRight();
    bool gesGrabDouble();

    bool gesCircle();
    bool gesCircleAnti();
    bool gesSwipe();
    bool gesKeyTap();
    bool gesScreenTap();

    int gesHandDirection();
private:
    Leap::Controller controller;

};

#endif // GESTURERECOGNITION_H
