#ifndef EVENTCONTROL_H
#define EVENTCONTROL_H

#include <QObject>

class EventControl : public QObject
{
    Q_OBJECT
public:
    explicit EventControl(QObject *parent = 0);

signals:

public slots:

};

#endif // EVENTCONTROL_H
