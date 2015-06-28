#ifndef DISPLAYTURNTABLE_H
#define DISPLAYTURNTABLE_H

#include <QWidget>

namespace Ui {
class DisplayTurntable;
}

class DisplayTurntable : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayTurntable(QWidget *parent = 0);
    ~DisplayTurntable();
    void paintEvent(QPaintEvent *event) ;

private:
    Ui::DisplayTurntable *ui;
    QPixmap m_Pixmap;
};

#endif // DISPLAYTURNTABLE_H
