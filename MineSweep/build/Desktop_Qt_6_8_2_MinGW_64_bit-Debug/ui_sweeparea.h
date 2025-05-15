/********************************************************************************
** Form generated from reading UI file 'sweeparea.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWEEPAREA_H
#define UI_SWEEPAREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SweepArea
{
public:

    void setupUi(QWidget *SweepArea)
    {
        if (SweepArea->objectName().isEmpty())
            SweepArea->setObjectName("SweepArea");
        SweepArea->resize(400, 300);

        retranslateUi(SweepArea);

        QMetaObject::connectSlotsByName(SweepArea);
    } // setupUi

    void retranslateUi(QWidget *SweepArea)
    {
        SweepArea->setWindowTitle(QCoreApplication::translate("SweepArea", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SweepArea: public Ui_SweepArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWEEPAREA_H
