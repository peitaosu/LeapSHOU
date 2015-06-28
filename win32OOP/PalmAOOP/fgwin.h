#ifndef FGWIN_H
#define FGWIN_H

#include <QObject>

class FGWin : public QObject
{
    Q_OBJECT
public:
    explicit FGWin(QObject *parent = 0);

signals:

public slots:
    int getFGWinName();



};

#endif // FGWIN_H
