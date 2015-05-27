#include "getinfo.h"
#include "vmouse.h"
#include <QApplication>
#include "data.h"
#include "sysctrl.h"
int main(int argc, char *argv[])
{
    dataListener listener;
    Controller controller;
    controller.addListener(listener);
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
    controller.config().save();
    QApplication a(argc, argv);
    GetInfo G;
    //w.show();
    vmouse v;
    v.show();
    SysCtrl s;


    return a.exec();
}
