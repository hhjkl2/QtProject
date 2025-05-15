/********************************************************************************
** Form generated from reading UI file 'customwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMWIDGET_H
#define UI_CUSTOMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton;

    void setupUi(QWidget *CustomWidget)
    {
        if (CustomWidget->objectName().isEmpty())
            CustomWidget->setObjectName("CustomWidget");
        CustomWidget->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CustomWidget->sizePolicy().hasHeightForWidth());
        CustomWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(CustomWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        pushButton_2 = new QPushButton(CustomWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color:green"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(CustomWidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color:blue"));

        verticalLayout->addWidget(pushButton_3);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        pushButton = new QPushButton(CustomWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setStyleSheet(QString::fromUtf8("background-color:red"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        retranslateUi(CustomWidget);

        QMetaObject::connectSlotsByName(CustomWidget);
    } // setupUi

    void retranslateUi(QWidget *CustomWidget)
    {
        CustomWidget->setWindowTitle(QCoreApplication::translate("CustomWidget", "Form", nullptr));
        pushButton_2->setText(QCoreApplication::translate("CustomWidget", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("CustomWidget", "PushButton", nullptr));
        pushButton->setText(QCoreApplication::translate("CustomWidget", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomWidget: public Ui_CustomWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMWIDGET_H
