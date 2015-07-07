#include <QCoreApplication>
#include "socketreceiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SocketReceiver S;
    return a.exec();
}
