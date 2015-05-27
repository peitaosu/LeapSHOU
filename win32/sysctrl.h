#ifndef SYSCTRL
#define SYSCTRL
#include <QObject>
class SysCtrl : public QObject
{
    Q_OBJECT
public:
    SysCtrl();
    ~SysCtrl();

public slots:
    void SendWM();
};
#endif // SYSCTRL

