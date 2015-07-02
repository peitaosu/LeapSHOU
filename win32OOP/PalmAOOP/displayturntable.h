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
    void paintEvent(QPaintEvent *event);
    void setFGWin(int);

public slots:
    void showDisplayTurntable(int, int);

private:
    Ui::DisplayTurntable *ui;
    QPixmap m_Pixmap_desktop;
    QPixmap m_Pixmap_filemanager;
    int FGWin;

};

#endif // DISPLAYTURNTABLE_H
