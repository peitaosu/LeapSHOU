#ifndef SOCKETRECEIVER_H
#define SOCKETRECEIVER_H

#include <QObject>
#include "operate.h"
class SocketReceiver : public QObject
{
    Q_OBJECT
public:
    explicit SocketReceiver(QObject *parent = 0);

signals:
    void sendUpS();
    void sendDownS();
    void sendLeftS();
    void sendRightS();
public slots:
    void receive();

private:
    Operate OP;
};

#endif // SOCKETRECEIVER_H
