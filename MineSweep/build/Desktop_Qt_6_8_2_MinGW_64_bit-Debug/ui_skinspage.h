/********************************************************************************
** Form generated from reading UI file 'skinspage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKINSPAGE_H
#define UI_SKINSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SkinsPage
{
public:

    void setupUi(QWidget *SkinsPage)
    {
        if (SkinsPage->objectName().isEmpty())
            SkinsPage->setObjectName("SkinsPage");
        SkinsPage->resize(400, 300);

        retranslateUi(SkinsPage);

        QMetaObject::connectSlotsByName(SkinsPage);
    } // setupUi

    void retranslateUi(QWidget *SkinsPage)
    {
        SkinsPage->setWindowTitle(QCoreApplication::translate("SkinsPage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SkinsPage: public Ui_SkinsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKINSPAGE_H
