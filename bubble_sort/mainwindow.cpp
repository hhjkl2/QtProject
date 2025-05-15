#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createLabels();
    updateLabel();
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   if(sorted == true){
       return;
   }

   if(j < n - i - 1){
       if(arr[j] > arr[j + 1]){
           int temp = arr[j];
           arr[j] = arr[j + 1];
           arr[j + 1] = temp;

           // 创建动画
           QPropertyAnimation *anim1 = new QPropertyAnimation(labels[j], "geometry");
           anim1->setDuration(500);  // 动画持续时间
           anim1->setStartValue(labels[j]->geometry());
           anim1->setEndValue(labels[j + 1]->geometry());

           QPropertyAnimation *anim2 = new QPropertyAnimation(labels[j + 1], "geometry");
           anim2->setDuration(500);
           anim2->setStartValue(labels[j + 1]->geometry());
           anim2->setEndValue(labels[j]->geometry());

           // 交换标签指针
           QLabel *tempLabel = labels[j];
           labels[j] = labels[j + 1];
           labels[j + 1] = tempLabel;

           // 启动动画
           anim1->start(QAbstractAnimation::DeleteWhenStopped);
           anim2->start(QAbstractAnimation::DeleteWhenStopped);
       }
       j++;
   }else{
       i++;
       j = 0;
       if(i >= n - 1){
           sorted = true;
       }
   }

   updateLabel();
}

void MainWindow::updateLabel()
{
   for (int k = 0; k < n; k++) {
       labels[k]->setText(QString::number(arr[k]));
   }
}

void MainWindow::createLabels()
{
   layout = new QHBoxLayout;
   QWidget * widget = new QWidget(this);
   widget->setLayout(layout);
   ui->verticalLayout->insertWidget(0, widget);

   for(int k = 0; k < n; k++){
       labels[k] = new QLabel(this);
       labels[k]->setAlignment(Qt::AlignCenter);
       layout->addWidget(labels[k]);
   }
}
