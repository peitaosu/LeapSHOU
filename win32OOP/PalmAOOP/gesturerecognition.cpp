#include "gesturerecognition.h"
#include <QApplication>
#include <QDesktopWidget>

int LhCount = 0;
int LHold[3] = {0};
int LHoldStatus = 0;
int RhCount = 0;
int RHold[3] = {0};
int RHoldStatus = 0;

GestureRecognition::GestureRecognition(){
    //开启Leap默认手势
    //enable Leap::Gesture
    controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
    controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
}

/*
 * 获取第一只手的手掌中心的稳定坐标的x
 * get x from 1st hand stabilized palm position
 */
float GestureRecognition::getX(){
    Leap::InteractionBox iBox = controller.frame().interactionBox();
    Leap::Vector handCenter = iBox.normalizePoint(
            controller.frame().hands()[0].stabilizedPalmPosition()
            );
    return handCenter.x;
}

/*
 * 获取第一只手的手掌中心的稳定坐标的y
 * get y from 1st hand stabilized palm position
 */
float GestureRecognition::getY(){

    Leap::InteractionBox iBox = controller.frame().interactionBox();
    Leap::Vector handCenter = iBox.normalizePoint(
            controller.frame().hands()[0].stabilizedPalmPosition()
            );
    return 1-handCenter.y;
}

/*
 * 获取第一只手的手掌中心的稳定坐标的z
 * get z from 1st hand stabilized palm position
 */
float GestureRecognition::getZ(){
    Leap::InteractionBox iBox = controller.frame().interactionBox();
    Leap::Vector handCenter = iBox.normalizePoint(
            controller.frame().hands()[0].stabilizedPalmPosition()
            );
    return handCenter.z;
}

/*
 * 获取当前的识别帧率
 * get current frames per second
 */
float GestureRecognition::getFPS(){
    return controller.frame().currentFramesPerSecond();
}

/*
 * 获取识别到的手的数量
 * get hands count
 */
int GestureRecognition::getHandsCount(){
    return controller.frame().hands().count();
}

/*
 * 获取特定数量帧的斜率
 * 输入值：int frames
 * get slope from frames
 * Import: int frames
 */
float GestureRecognition::getSlope(int frames){
    //定义int型数组fitPos_x和fitPos_y，大小为frames
    //new integer array fitPos_x and fitPos_y, both size is frames
    int *fitPos_x;
    int *fitPos_y;
    fitPos_x = (int *) malloc(sizeof(int) * frames);
    fitPos_y = (int *) malloc(sizeof(int) * frames);

    //获取最近的frames帧中，第1只手的稳定的手掌中心坐标，保存到数组fitPos_x和fitPos_y中
    //get 1st hand stabilized palm position early frames frames and save to fitPos_x and fitPos_y
    int UserDeviceScreenWidth = QApplication::desktop()->width();
    int UserDeviceScreenHeight = QApplication::desktop()->height();
    Leap::InteractionBox iBox = controller.frame().interactionBox();
    for(int p=0;p<frames;p++){
        fitPos_x[p] = iBox.normalizePoint(controller.frame(p).hands()[0].stabilizedPalmPosition()).x * UserDeviceScreenWidth;
        fitPos_y[p] = iBox.normalizePoint(controller.frame(p).hands()[0].stabilizedPalmPosition()).y * UserDeviceScreenHeight;
    }

    czy::Fit fit;
    //最小二乘法拟合
    //OLS(Ordinary Least Squares)
    fit.polyfit(fitPos_x,fitPos_y,frames,2,true);

    return fit.getSlope();
}

/*
 * 手势：最左侧手悬停
 * 阙值：30f*3
 * Gesture: Hold Left Most
 * Threshold: 30f*3
 */
int GestureRecognition::gesHoldLeft(){
    //每间隔30帧进行一次处理
    //process in every 30 frames
    if(controller.frame().id()%30 == 0 && !controller.frame().hands().isEmpty()){
        //定义int型数组fitPos_x和fitPos_y，大小为60
        //new integer array fitPos_x and fitPos_y, both size is 60
        int fitPos_x[60];
        int fitPos_y[60];
        //获取最近的60帧中，最左侧手的稳定的手掌中心坐标，保存到数组fitPos_x和fitPos_y中
        //get left most hand stabilized palm position early 60 frames and save to fitPos_x and fitPos_y
        int UserDeviceScreenWidth = QApplication::desktop()->width();
        int UserDeviceScreenHeight = QApplication::desktop()->height();
        Leap::InteractionBox iBox = controller.frame().interactionBox();
        for(int p=0;p<60;p++){
            fitPos_x[p] = iBox.normalizePoint(controller.frame(p).hands().leftmost().stabilizedPalmPosition()).x * UserDeviceScreenWidth;
            fitPos_y[p] = iBox.normalizePoint(controller.frame(p).hands().leftmost().stabilizedPalmPosition()).y * UserDeviceScreenHeight;
        }
        czy::Fit fit;
        //计算60帧的平均值
        //get every 60 frames mean
        int PosXM = fit.Mean(fitPos_x,60);
        int PosYM = fit.Mean(fitPos_y,60);

        /*
         * 判断坐标变动是否维持在悬停区间[-5,5]中
         * 如果1次为真，计数加1，若连续3次为真，则判断手势为真。
         * Determines whether the coordinates change remain in hover interval [-5,5]
         * if true in one time, count add 1;
         * if true for 3 times, gesture is true.
         * if false, reset.
         */
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

    /*
     * 根据不同的持续时间得到不同的悬停状态
     * get different hold status according to the difference between keep time
     * 000,100,110,111
     */
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

/*
 * 手势：最右侧手悬停
 * 阙值：30f*3
 * Gesture: Hold Right Most
 * Threshold: 30f*3
 */
int GestureRecognition::gesHoldRight(){
    //每间隔30帧进行一次处理
    //process in every 30 frames
    if(controller.frame().id()%30 == 0 && !controller.frame().hands().isEmpty()){
        //定义int型数组fitPos_x和fitPos_y，大小为60
        //new integer array fitPos_x and fitPos_y, both size is 60
        int fitPos_x[60];
        int fitPos_y[60];
        //获取最近的60帧中，最右侧手的稳定的手掌中心坐标，保存到数组fitPos_x和fitPos_y中
        //get right most hand stabilized palm position early 60 frames and save to fitPos_x and fitPos_y
        int UserDeviceScreenWidth = QApplication::desktop()->width();
        int UserDeviceScreenHeight = QApplication::desktop()->height();
        Leap::InteractionBox iBox = controller.frame().interactionBox();
        for(int p=0;p<60;p++){
            fitPos_x[p] = iBox.normalizePoint(controller.frame(p).hands().rightmost().stabilizedPalmPosition()).x * UserDeviceScreenWidth;
            fitPos_y[p] = iBox.normalizePoint(controller.frame(p).hands().rightmost().stabilizedPalmPosition()).y * UserDeviceScreenHeight;
        }
        czy::Fit fit;
        //计算60帧的平均值
        //get every 60 frames mean
        int PosXM = fit.Mean(fitPos_x,60);
        int PosYM = fit.Mean(fitPos_y,60);

        /*
         * 判断坐标变动是否维持在悬停区间[-5,5]中
         * 如果1次为真，计数加1，若连续3次为真，则判断手势为真。
         * Determines whether the coordinates change remain in hover interval [-5,5]
         * if true in one time, count add 1;
         * if true for 3 times, gesture is true.
         * if false, reset.
         */
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

    /*
     * 根据不同的持续时间得到不同的悬停状态
     * get different hold status according to the difference between keep time
     * 000,100,110,111
     */
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
/*
 * 手势：双手悬停
 * 阙值：30f*3
 * Gesture: Hold Left and Right Most
 * Threshold: 30f*3
 */
int GestureRecognition::gesHoldDouble(){
    //分别对最左侧和最右侧的手进行处理和判断
    //process and determine the hands leftmost and rightmost
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

/*
 * 手势：最左侧手捏合
 * 阙值：0.80
 * Gesture: Pinch Left Most
 * Threshold: 0.80
 */
bool GestureRecognition::gesPinchLeft(){
    int Threshold = 0.80;
    Leap::Hand handLeft = controller.frame().hands().leftmost();
    if(handLeft.pinchStrength() >= Threshold){
        return 1;
    }else{
        return 0;
    }
}

/*
 * 手势：最右侧手捏合
 * 阙值：0.80
 * Gesture: Pinch Right Most
 * Threshold: 0.80
 */
bool GestureRecognition::gesPinchRight(){
    int Threshold = 0.80;
    Leap::Hand handRight = controller.frame().hands().rightmost();
    if(handRight.pinchStrength() >= Threshold){
        return 1;
    }else{
        return 0;
    }
}

/*
 * 手势：双手捏合
 * 阙值：0.80
 * Gesture: Pinch Double
 * Threshold: 0.80
 */
bool GestureRecognition::gesPinchDouble(){
    int Threshold = 0.80;
    if(controller.frame().hands().count() == 2){
        Leap::Hand handLeft = controller.frame().hands().leftmost();
        Leap::Hand handRight = controller.frame().hands().rightmost();
        if(handLeft.pinchStrength() >= Threshold && handRight.pinchStrength() >= Threshold){
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

/*
 * 手势：最左侧手握拳
 * 阙值：0.95
 * Gesture: Grab Left Most
 * Threshold: 0.95
 */
bool GestureRecognition::gesGrabLeft(){
    int Threshold = 0.95;
    Leap::Hand handLeft = controller.frame().hands().leftmost();
    if(handLeft.grabStrength() >= Threshold){
        return 1;
    }else{
        return 0;
    }
}

/*
 * 手势：最右侧手握拳
 * 阙值：0.95
 * Gesture: Grab Right Most
 * Threshold: 0.95
 */
bool GestureRecognition::gesGrabRight(){
    int Threshold = 0.95;
    Leap::Hand handRight = controller.frame().hands().rightmost();
    if(handRight.grabStrength() >= Threshold){
        return 1;
    }else{
        return 0;
    }
}

/*
 * 手势：双手握拳
 * 阙值：0.95
 * Gesture: Grab Double
 * Threshold: 0.95
 */
bool GestureRecognition::gesGrabDouble(){
    int Threshold = 0.95;
    if(controller.frame().hands().count() == 2){
        Leap::Hand handLeft = controller.frame().hands().leftmost();
        Leap::Hand handRight = controller.frame().hands().rightmost();
        if(handLeft.grabStrength() >= Threshold && handRight.grabStrength() >= Threshold){
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

/*
 * 手势：顺时针画圈
 * Gesture: Circle
 */
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

/*
 * 手势：逆时针画圈
 * Gesture: Circle-Anti
 */
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

/*
 * 手势：手部切换
 * Gesture: Swipe
 */
bool GestureRecognition::gesSwipe(){
    Leap::Gesture gesture = controller.frame().gestures()[0];
    if(gesture.type() == Leap::Gesture::TYPE_SWIPE) {
        return 1;
    }else{
        return 0;
    }
}

/*
 * 手势：点击键盘
 * Gesture: Key Tap
 */
bool GestureRecognition::gesKeyTap(){
    Leap::Gesture gesture = controller.frame().gestures()[0];
    if(gesture.type() == Leap::Gesture::TYPE_KEY_TAP) {
        return 1;
    }else{
        return 0;
    }
}

/*
 * 手势：点击屏幕
 * Gesture: Screen Tap
 */
bool GestureRecognition::gesScreenTap(){
    Leap::Gesture gesture = controller.frame().gestures()[0];
    if(gesture.type() == Leap::Gesture::TYPE_SCREEN_TAP) {
        return 1;
    }else{
        return 0;
    }
}

/*
 * 手势：手部运动方向
 * 左、右、上、下、前、后
 * 阙值：1500
 * Gesture: Hand Direction
 * Left Right Up Down Forward Backward
 * Threshold: 1500
 */
int GestureRecognition::gesHandDirection(){
    Leap::Vector handSpeed = controller.frame().fingers()[0].tipVelocity();
    int Threshold = 1500;
    if(handSpeed.x > Threshold){
        //LEFT
        return 1;
    }else if(handSpeed.x < -Threshold){
        //RIGHT
        return 2;
    }
    if(handSpeed.y > Threshold){
        //UP
        return 3;
    }else if(handSpeed.y < -Threshold){
        //DOWN
        return 4;
    }
    if(handSpeed.z > Threshold){
        //FORWARD
        return 5;
    }else if(handSpeed.z < -Threshold){
        //BACKWARD
        return 6;
    }
    return 0;
}
