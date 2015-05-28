#ifndef FGWINLISTENER_H
#define FGWINLISTENER_H

#include <QObject>

class FGWinListener : public QObject
{
    Q_OBJECT
public:
    explicit FGWinListener(QObject *parent = 0);
    ~FGWinListener();

signals:

public slots:
};

#endif // FGWINLISTENER_H
