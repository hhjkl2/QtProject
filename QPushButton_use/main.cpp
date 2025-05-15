#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QPushButton>
#include <QFont>

void onPushButtonClicked(){
    qDebug() << "执行了onPushButtonClicked";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    QPushButton* btn = new QPushButton(&w);
    btn->setGeometry(100,100,200,200);
    btn->setText("点击");
    QFont font("Arial",12,QFont::Bold);
    btn->setFont(font);
    btn->connect(btn,&QPushButton::clicked,onPushButtonClicked);
    btn->show();

    return a.exec();
}

