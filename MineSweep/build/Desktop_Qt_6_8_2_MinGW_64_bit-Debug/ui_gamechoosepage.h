/********************************************************************************
** Form generated from reading UI file 'gamechoosepage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMECHOOSEPAGE_H
#define UI_GAMECHOOSEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameChoosePage
{
public:

    void setupUi(QWidget *GameChoosePage)
    {
        if (GameChoosePage->objectName().isEmpty())
            GameChoosePage->setObjectName("GameChoosePage");
        GameChoosePage->resize(400, 300);

        retranslateUi(GameChoosePage);

        QMetaObject::connectSlotsByName(GameChoosePage);
    } // setupUi

    void retranslateUi(QWidget *GameChoosePage)
    {
        GameChoosePage->setWindowTitle(QCoreApplication::translate("GameChoosePage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameChoosePage: public Ui_GameChoosePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMECHOOSEPAGE_H
