#ifndef DISPLAYSTATUS_H
#define DISPLAYSTATUS_H

#include <QWidget>
#include <QTime>
namespace Ui {
class DisplayStatus;
}

class DisplayStatus : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayStatus(QWidget *parent = 0);
    ~DisplayStatus();
    void delayShow();
public slots:
    void setStatusDisplay();

private:
    Ui::DisplayStatus *ui;
    QTime current_time;
};

#endif // DISPLAYSTATUS_H
