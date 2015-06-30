#ifndef LMENGINEERINGMODEL_H
#define LMENGINEERINGMODEL_H

#include <QWidget>

namespace Ui {
class LMEngineeringModel;
}

class LMEngineeringModel : public QWidget
{
    Q_OBJECT

public:
    explicit LMEngineeringModel(QWidget *parent = 0);
    ~LMEngineeringModel();

private:
    Ui::LMEngineeringModel *ui;
};

#endif // LMENGINEERINGMODEL_H
