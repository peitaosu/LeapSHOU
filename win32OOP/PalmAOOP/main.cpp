#include <QApplication>
#include"gesturerecognition.h"
#include"debug.h"
#include "eventcontrol.h"
#include "drawgesture.h"
#include "settingpanel.h"
#include "roadmapgesture.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //debug d;
    EventControl E;
    RoadMapGesture RMG;
    RMG.show();
//    SettingPanel SP;
//    SP.show();


    return a.exec();
}
