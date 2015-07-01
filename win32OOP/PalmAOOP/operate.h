#ifndef OPERATE_H
#define OPERATE_H

#include <QObject>

class Operate : public QObject
{
    Q_OBJECT
public:
    explicit Operate(QObject *parent = 0);

signals:

public slots:

    void MouseLeftClick(int,int);
    void MouseLeftDClick(int,int);
    void MouseRightClick(int,int);
    void MouseWheel();
    void MouseWheelN();
    void MouseWheel(int);
    void MouseWheelStop();
    void showDesktop();
    void openFileManager();
    void swipeWindow();
    void swipeWindow(int);
    void swipeBrowserTab();
    void moveWindowtoLeft();
    void moveWindowtoRight();
    void moveWindowtoUp();
    void moveWindowtoDown();
    void openBrowser();


};

#endif // OPERATE_H
