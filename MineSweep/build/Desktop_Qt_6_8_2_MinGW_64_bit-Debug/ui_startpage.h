/********************************************************************************
** Form generated from reading UI file 'startpage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTPAGE_H
#define UI_STARTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartPage
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *MainLayout;
    QPushButton *StartButton;
    QPushButton *ChangeSkins;
    QPushButton *EixtGame;

    void setupUi(QWidget *StartPage)
    {
        if (StartPage->objectName().isEmpty())
            StartPage->setObjectName("StartPage");
        StartPage->resize(181, 111);
        StartPage->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        verticalLayoutWidget = new QWidget(StartPage);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 181, 111));
        MainLayout = new QVBoxLayout(verticalLayoutWidget);
        MainLayout->setObjectName("MainLayout");
        MainLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        MainLayout->setContentsMargins(0, 0, 0, 0);
        StartButton = new QPushButton(verticalLayoutWidget);
        StartButton->setObjectName("StartButton");

        MainLayout->addWidget(StartButton);

        ChangeSkins = new QPushButton(verticalLayoutWidget);
        ChangeSkins->setObjectName("ChangeSkins");

        MainLayout->addWidget(ChangeSkins);

        EixtGame = new QPushButton(verticalLayoutWidget);
        EixtGame->setObjectName("EixtGame");

        MainLayout->addWidget(EixtGame);


        retranslateUi(StartPage);

        QMetaObject::connectSlotsByName(StartPage);
    } // setupUi

    void retranslateUi(QWidget *StartPage)
    {
        StartPage->setWindowTitle(QCoreApplication::translate("StartPage", "Form", nullptr));
        StartButton->setText(QCoreApplication::translate("StartPage", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        ChangeSkins->setText(QCoreApplication::translate("StartPage", "\346\233\264\346\215\242\345\244\226\350\247\202", nullptr));
        EixtGame->setText(QCoreApplication::translate("StartPage", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartPage: public Ui_StartPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTPAGE_H
