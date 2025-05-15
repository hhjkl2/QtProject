/********************************************************************************
** Form generated from reading UI file 'gamesizeedit.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESIZEEDIT_H
#define UI_GAMESIZEEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameSizeEdit
{
public:

    void setupUi(QWidget *GameSizeEdit)
    {
        if (GameSizeEdit->objectName().isEmpty())
            GameSizeEdit->setObjectName("GameSizeEdit");
        GameSizeEdit->resize(423, 297);

        retranslateUi(GameSizeEdit);

        QMetaObject::connectSlotsByName(GameSizeEdit);
    } // setupUi

    void retranslateUi(QWidget *GameSizeEdit)
    {
        GameSizeEdit->setWindowTitle(QCoreApplication::translate("GameSizeEdit", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameSizeEdit: public Ui_GameSizeEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESIZEEDIT_H
