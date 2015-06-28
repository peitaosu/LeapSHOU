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
    void MouseWheel(int);
    void showDesktop();
    void openFileManager();
    void swipeWindow();
    void swipeWindow(int);


};

#endif // OPERATE_H
