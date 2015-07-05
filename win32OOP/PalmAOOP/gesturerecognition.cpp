#include "gesturerecognition.h"
#include <QApplication>
#include <QDesktopWidget>

int LhCount = 0;
int LHold[3] = {0};
int RhCount = 0;
int RHold[3] = {0};
int LHoldStatus = 0;
int RHoldStatus = 0;

GestureRecognition::GestureRecognition(){
    controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
    controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
}

float GestureRecognition::getX(){
    Leap::InteractionBox iBox = controller.frame().interactionBox();
    Leap::Vector handCenter = iBox.normalizePoint(
            controller.frame().hands()[0].stabilizedPalmPosition()
            );
    return handCenter.x;
}

float GestureRecognition::getY(){
    Leap::InteractionBox iBox = controller.frame().interactionBox();
    Leap::Vector handCenter = iBox.normalizePoint(
            controller.frame().hands()[0].stabilizedPalmPosition()
            );
    return 1-handCenter.y;
}

float GestureRecognition::getZ(){
    Leap::InteractionBox iBox = controller.frame().interactionBox();
    Leap::Vector handCenter = iBox.normalizePoint(
            controller.frame().hands()[0].stabilizedPalmPosition()
            );
    return handCenter.z;
}

float GestureRecognition::getFPS(){
    return controller.frame().currentFramesPerSecond();
}

float GestureRecognition::getSlope(int frames){
    int *fitPos_x;
    int *fitPos_y;
    fitPos_x = (int *) malloc(sizeof(int) * frames);
    fitPos_y = (int *) malloc(sizeof(int) * frames);
    int UserDeviceScreenWidth = QApplication::desktop()->width();
    int UserDeviceScreenHeight = QApplication::desktop()->height();

    Leap::InteractionBox iBox = controller.frame().interactionBox();
    for(int p=0;p<frames;p++){
        fitPos_x[p] = iBox.normalizePoint(controller.frame(p).hands()[0].stabilizedPalmPosition()).x * UserDeviceScreenWidth;
        fitPos_y[p] = iBox.normalizePoint(controller.frame(p).hands()[0].stabilizedPalmPosition()).y * UserDeviceScreenHeight;
    }

    czy::Fit fit;

    fit.polyfit(fitPos_x,fitPos_y,frames,2,true);
    return fit.getSlope();
}

int GestureRecognition::gesHoldLeft(){
    if(controller.frame().id()%30 == 0 && !controller.frame().hands().isEmpty()){
        int fitPos_x[60];
        int fitPos_y[60];
        int UserDeviceScreenWidth = QApplication::desktop()->width();
        int UserDeviceScreenHeight = QApplication::desktop()->height();
        Leap::InteractionBox iBox = controller.frame().interactionBox();
        for(int p=0;p<60;p++){
            fitPos_x[p] = iBox.normalizePoint(controller.frame(p).hands().leftmost().stabilizedPalmPosition()).x * UserDeviceScreenWidth;
            fitPos_y[p] = iBox.normalizePoint(controller.frame(p).hands().leftmost().stabilizedPalmPosition()).y * UserDeviceScreenHeight;
        }
        czy::Fit fit;
        int PosXM = fit.Mean(fitPos_x,60);
        int PosYM = fit.Mean(fitPos_y,60);

        if(fitPos_x[0] >= (PosXM-5) && fitPos_x[0] <= (PosXM+5) && fitPos_y[0] >= (PosYM-5) && fitPos_y[0] <= (PosYM+5)){
            LHold[LhCount] = 1;
            LhCount++;
        }else{
            if(LhCount != 0){
                LHold[0] = 0;
                LHold[1] = 0;
                LHold[2] = 0;
                LhCount = 0;
            }
        }
    }
    if(LHold[0] == 1 && LHold[1] == 1 && LHold[2] == 1){
        LHoldStatus = 3;
        LHold[0] = 0;
        LHold[1] = 0;
        LHold[2] = 0;
        LhCount = 0;
        return 3;
    }else if(LHold[0] == 1 && LHold[1] == 1 && LHold[2] == 0){
        LHoldStatus = 2;
        return 2;
    }else if(LHold[0] == 1 && LHold[1] == 0 && LHold[2] == 0){
        LHoldStatus = 1;
        return 1;
    }else{
        if(LHoldStatus == 3){
            return 4;
            LHoldStatus = 4;
        }else{
            LHoldStatus = 0;
            return 0;
        }
    }
}
int GestureRecognition::gesHoldRight(){
    if(controller.frame().id()%30 == 0 && !controller.frame().hands().isEmpty()){
        int fitPos_x[60];
        int fitPos_y[60];
        int UserDeviceScreenWidth = QApplication::desktop()->width();
        int UserDeviceScreenHeight = QApplication::desktop()->height();
        Leap::InteractionBox iBox = controller.frame().interactionBox();
        for(int p=0;p<60;p++){
            fitPos_x[p] = iBox.normalizePoint(controller.frame(p).hands().rightmost().stabilizedPalmPosition()).x * UserDeviceScreenWidth;
            fitPos_y[p] = iBox.normalizePoint(controller.frame(p).hands().rightmost().stabilizedPalmPosition()).y * UserDeviceScreenHeight;
        }
        czy::Fit fit;
        int PosXM = fit.Mean(fitPos_x,60);
        int PosYM = fit.Mean(fitPos_y,60);

        if(fitPos_x[0] >= (PosXM-5) && fitPos_x[0] <= (PosXM+5) && fitPos_y[0] >= (PosYM-5) && fitPos_y[0] <= (PosYM+5)){
            RHold[RhCount] = 1;
            RhCount++;
        }else{
            if(RhCount != 0){
                RHold[0] = 0;
                RHold[1] = 0;
                RHold[2] = 0;
                RhCount = 0;
            }
        }
    }
    if(RHold[0] == 1 && RHold[1] == 1 && RHold[2] == 1){
        RHoldStatus = 3;
        RHold[0] = 0;
        RHold[1] = 0;
        RHold[2] = 0;
        RhCount = 0;
        return 3;
    }else if(RHold[0] == 1 && RHold[1] == 1 && RHold[2] == 0){
        RHoldStatus = 2;
        return 2;
    }else if(RHold[0] == 1 && RHold[1] == 0 && RHold[2] == 0){
        RHoldStatus = 1;
        return 1;
    }else{
        if(RHoldStatus == 3){
            RHoldStatus = 4;
            return 4;
        }else{
            RHoldStatus = 0;
            return 0;
        }
    }
}
int GestureRecognition::gesHoldDouble(){
    gesHoldLeft();
    gesHoldRight();
    for(int i = 0;i<3;i++){
        std::cout<<LHold[i]<<"+"<<RHold[i]<<std::endl;
    }
    if(        RHold[0] == 1
            && RHold[1] == 1
            && RHold[2] == 1
            && LHold[0] == 1
            && LHold[1] == 1
            && LHold[2] == 1
               ){
        return 3;
    }else if(   RHold[0] == 1
             && RHold[1] == 1
             && RHold[2] == 0
             && LHold[0] == 1
             && LHold[1] == 1
             && LHold[2] == 0
                ){
        return 2;
    }else if(   RHold[0] == 1
             && RHold[1] == 0
             && RHold[2] == 0
             && LHold[0] == 1
             && LHold[1] == 0
             && LHold[2] == 0
                ){
        return 1;
    }else{
        return 0;
    }
}
bool GestureRecognition::gesPinchLeft(){
    Leap::Hand handLeft = controller.frame().hands().leftmost();
    if(handLeft.pinchStrength() >= 0.95){
        return 1;
    }else{
        return 0;
    }
}
bool GestureRecognition::gesPinchRight(){
    Leap::Hand handRight = controller.frame().hands().rightmost();
    if(handRight.pinchStrength() >= 0.95){
        return 1;
    }else{
        return 0;
    }
}
bool GestureRecognition::gesPinchDouble(){
    if(controller.frame().hands().count() == 2){
        Leap::Hand handLeft = controller.frame().hands().leftmost();
        Leap::Hand handRight = controller.frame().hands().rightmost();
        if(handLeft.pinchStrength() >= 0.95 && handRight.pinchStrength() >= 0.95){
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}
bool GestureRecognition::gesGrabLeft(){
    Leap::Hand handLeft = controller.frame().hands().leftmost();
    if(handLeft.grabStrength() >= 0.95){
        return 1;
    }else{
        return 0;
    }
}
bool GestureRecognition::gesGrabRight(){
    Leap::Hand handRight = controller.frame().hands().rightmost();
    if(handRight.grabStrength() >= 0.95){
        return 1;
    }else{
        return 0;
    }
}
bool GestureRecognition::gesGrabDouble(){
    if(controller.frame().hands().count() == 2){
        Leap::Hand handLeft = controller.frame().hands().leftmost();
        Leap::Hand handRight = controller.frame().hands().rightmost();
        if(handLeft.grabStrength() >= 0.95 && handRight.grabStrength() >= 0.95){
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

bool GestureRecognition::gesCircle(){
    Leap::Gesture gesture = controller.frame().gestures()[0];
    if(gesture.type() == Leap::Gesture::TYPE_CIRCLE) {
        Leap::CircleGesture circle = gesture;
        if (circle.pointable().direction().angleTo(circle.normal()) <= 3.1415926/2) {
            return 1;
        } else {
            return 0;
        }
    }else{
        return 0;
    }
}
bool GestureRecognition::gesCircleAnti(){
    Leap::Gesture gesture = controller.frame().gestures()[0];
    if(gesture.type() == Leap::Gesture::TYPE_CIRCLE) {
        Leap::CircleGesture circle = gesture;
        if (circle.pointable().direction().angleTo(circle.normal()) <= 3.1415926/2) {
            return 0;
        } else {
            return 1;
        }
    }else{
        return 0;
    }
}

bool GestureRecognition::gesSwipe(){
    Leap::Gesture gesture = controller.frame().gestures()[0];
    if(gesture.type() == Leap::Gesture::TYPE_SWIPE) {
        return 1;
    }else{
        return 0;
    }
}

bool GestureRecognition::gesKeyTap(){
    Leap::Gesture gesture = controller.frame().gestures()[0];
    if(gesture.type() == Leap::Gesture::TYPE_KEY_TAP) {
        return 1;
    }else{
        return 0;
    }
}

bool GestureRecognition::gesScreenTap(){
    Leap::Gesture gesture = controller.frame().gestures()[0];
    if(gesture.type() == Leap::Gesture::TYPE_SCREEN_TAP) {
        return 1;
    }else{
        return 0;
    }
}

int GestureRecognition::gesHandDirection(){
    Leap::Vector handSpeed = controller.frame().fingers()[0].tipVelocity();
    if(handSpeed.x > 1000){
        //LEFT
        return 1;
    }else if(handSpeed.x < -1000){
        //RIGHT
        return 2;
    }
    if(handSpeed.y > 1000){
        //UP
        return 3;
    }else if(handSpeed.y < -1000){
        //DOWN
        return 4;
    }
    if(handSpeed.z > 1000){
        //FORWARD
        return 5;
    }else if(handSpeed.z < -1000){
        //BACKWARD
        return 6;
    }
    return 0;
}
