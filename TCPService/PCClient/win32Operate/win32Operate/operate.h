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
    void sendUp();
    void sendDown();
};

#endif // OPERATE_H
