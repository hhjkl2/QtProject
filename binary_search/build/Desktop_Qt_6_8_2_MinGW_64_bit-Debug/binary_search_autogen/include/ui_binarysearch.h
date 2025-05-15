/********************************************************************************
** Form generated from reading UI file 'binarysearch.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BINARYSEARCH_H
#define UI_BINARYSEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BinarySearch
{
public:
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QGraphicsView *graphicsView;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QLineEdit *editTarget;
    QPushButton *btnStart;
    QPushButton *btnNext;
    QLabel *lblStatus;

    void setupUi(QWidget *BinarySearch)
    {
        if (BinarySearch->objectName().isEmpty())
            BinarySearch->setObjectName("BinarySearch");
        centralwidget = new QWidget(BinarySearch);
        centralwidget->setObjectName("centralwidget");
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName("vboxLayout");
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setMinimumSize(QSize(0, 200));

        vboxLayout->addWidget(graphicsView);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        hboxLayout->addWidget(label);

        editTarget = new QLineEdit(centralwidget);
        editTarget->setObjectName("editTarget");

        hboxLayout->addWidget(editTarget);

        btnStart = new QPushButton(centralwidget);
        btnStart->setObjectName("btnStart");

        hboxLayout->addWidget(btnStart);

        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName("btnNext");

        hboxLayout->addWidget(btnNext);


        vboxLayout->addLayout(hboxLayout);

        lblStatus = new QLabel(centralwidget);
        lblStatus->setObjectName("lblStatus");

        vboxLayout->addWidget(lblStatus);


        retranslateUi(BinarySearch);

        QMetaObject::connectSlotsByName(BinarySearch);
    } // setupUi

    void retranslateUi(QWidget *BinarySearch)
    {
        label->setText(QCoreApplication::translate("BinarySearch", "\347\233\256\346\240\207\345\200\274:", nullptr));
        btnStart->setText(QCoreApplication::translate("BinarySearch", "\345\274\200\345\247\213\346\220\234\347\264\242", nullptr));
        btnNext->setText(QCoreApplication::translate("BinarySearch", "\344\270\213\344\270\200\346\255\245", nullptr));
        lblStatus->setText(QCoreApplication::translate("BinarySearch", "\345\260\261\347\273\252", nullptr));
        (void)BinarySearch;
    } // retranslateUi

};

namespace Ui {
    class BinarySearch: public Ui_BinarySearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BINARYSEARCH_H
