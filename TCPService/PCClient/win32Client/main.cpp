#include "vmouse.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vmouse v;
    v.show();
    return a.exec();
}
