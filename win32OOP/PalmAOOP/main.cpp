#include <QApplication>
#include "eventcontrol.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EventControl E;
    return a.exec();
}
