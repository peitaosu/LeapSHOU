#ifndef VMOUSE_H
#define VMOUSE_H

#include <QWidget>
#include "lmlistener.h"
<<<<<<< HEAD

class LMListener;

=======
>>>>>>> origin/master
class VMouse : public QWidget
{
    Q_OBJECT
public:
    explicit VMouse(QWidget *parent = 0);
    ~VMouse();
<<<<<<< HEAD

=======
    void mouseUpdate();
    void screenUpdate();
>>>>>>> origin/master

signals:

public slots:
    void paintEvent(QPaintEvent *event);
private:

    int mouse_x;
    int mouse_y;
    int screen_x;
    int screen_y;
    int UserDeviceScreenWidth;
    int UserDeviceScreenHeight;






    //Leap::Vector handCenter;

//friend class LMListener;
};

#endif // VMOUSE_H
