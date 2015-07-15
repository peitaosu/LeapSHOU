/********************************************************************************
** Form generated from reading UI file 'vmouse.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VMOUSE_H
#define UI_VMOUSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vmouse
{
public:

    void setupUi(QWidget *vmouse)
    {
        if (vmouse->objectName().isEmpty())
            vmouse->setObjectName(QStringLiteral("vmouse"));
        vmouse->resize(400, 300);

        retranslateUi(vmouse);

        QMetaObject::connectSlotsByName(vmouse);
    } // setupUi

    void retranslateUi(QWidget *vmouse)
    {
        vmouse->setWindowTitle(QApplication::translate("vmouse", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class vmouse: public Ui_vmouse {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VMOUSE_H
