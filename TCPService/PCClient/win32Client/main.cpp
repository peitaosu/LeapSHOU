#include "vmouse.h"
#include <QApplication>
#include "display.h"
#include <Windows.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vmouse v;
    v.show();
    display dp;
    dp.show();
    return a.exec();
}
