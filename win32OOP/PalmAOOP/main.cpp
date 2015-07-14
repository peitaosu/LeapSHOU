#include <QApplication>
#include"gesturerecognition.h"
#include"debug.h"
#include "eventcontrol.h"
#include "drawgesture.h"
#include "settingpanel.h"
int main(int argc, char *argv[])
{
    //QApplication::addLibraryPath("./plugins");
    QApplication a(argc, argv);
    //debug d;
    EventControl E;
//    SettingPanel SP;
//    SP.show();


    return a.exec();
}
