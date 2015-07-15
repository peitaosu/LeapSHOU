/********************************************************************************
** Form generated from reading UI file 'display.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_display
{
public:
    QLabel *nolabel;

    void setupUi(QWidget *display)
    {
        if (display->objectName().isEmpty())
            display->setObjectName(QStringLiteral("display"));
        display->resize(180, 180);
        nolabel = new QLabel(display);
        nolabel->setObjectName(QStringLiteral("nolabel"));
        nolabel->setGeometry(QRect(0, 0, 180, 180));
        QFont font;
        font.setFamily(QStringLiteral("Adobe Arabic"));
        font.setPointSize(180);
        font.setBold(true);
        font.setWeight(75);
        nolabel->setFont(font);
        nolabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        nolabel->setAlignment(Qt::AlignCenter);

        retranslateUi(display);

        QMetaObject::connectSlotsByName(display);
    } // setupUi

    void retranslateUi(QWidget *display)
    {
        display->setWindowTitle(QApplication::translate("display", "Form", 0));
        nolabel->setText(QApplication::translate("display", "0", 0));
    } // retranslateUi

};

namespace Ui {
    class display: public Ui_display {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAY_H
