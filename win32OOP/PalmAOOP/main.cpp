#include "gestureshow.h"
#include <QApplication>
#include "vmouse.h"
#include "lmlistener.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //GestureShow w;
    //w.show();
    VMouse v;
    v.show();
    LMListener listener;
    Controller controller;
    controller.addListener(listener);


    return a.exec();
}
