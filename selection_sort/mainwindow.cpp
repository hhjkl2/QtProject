#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createLabels();
    initLabels();
    updateLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    if (sorted) return;

    do{
        if(j < n){
            if (arr[j] < arr[minIndex]) {
                labels[minIndex]->setStyleSheet("background-color: lightgray;");
                minIndex = j;
                labels[minIndex]->setStyleSheet("background-color: yellow;");
            }
            if(minIndex != j){//②如果当前位置不为黄光，则消除蓝光
                labels[j]->setStyleSheet("background-color: lightgray;");
            }
            j++;
            if(j != n){//①下一个检查位置为蓝光
                labels[j]->setStyleSheet("background-color: blue;");
            }
            }else{
            if(minIndex != i){
                int temp = arr[i];
                arr[i] = arr[minIndex];
                arr[minIndex] = temp;
                swapLabels(i, minIndex);
            }
            labels[i]->setStyleSheet("background-color: lightgray;");//①在经过swapLabels后i位置上是黄光②i位置本身就是黄光  -》 i位置上必定有黄光要消除它

            i++;
            if(i >= n - 1){
                sorted = true;
                break;
            }
            j = i + 1;
            if(j != n){//①下一个检查位置为蓝光
                labels[j]->setStyleSheet("background-color: blue;");
            }
            minIndex = i;
            labels[minIndex]->setStyleSheet("background-color: yellow;");
        }
    }while(0);//提供给内部的if跳出

    updateLabels();
}

void MainWindow::createLabels(){
    arrayLayout = new QHBoxLayout;
    QWidget *widget = new QWidget(this);
    widget->setLayout(arrayLayout);
    ui->verticalLayout->insertWidget(0, widget);

    for (int k = 0; k < n; k++) {
        labels[k] = new QLabel(QString::number(arr[k]), this);
        labels[k]->setAlignment(Qt::AlignCenter);
        labels[k]->setStyleSheet("background-color: lightgray;");
        arrayLayout->addWidget(labels[k]);
    }

    //arrayLayout->setSpacing(5); // Set the spacing between labels
    //arrayLayout->setAlignment(Qt::AlignLeft); // Set the alignment of the labels
}

void MainWindow::updateLabels(){
    for (int k = 0; k < n; k++) {
        labels[k]->setText(QString::number(arr[k]));
    }
}

void MainWindow::swapLabels(int index1, int index2){
    QPropertyAnimation *anim1 = new QPropertyAnimation(labels[index1], "geometry");
    anim1->setDuration(500);
    anim1->setStartValue(labels[index1]->geometry());
    anim1->setEndValue(labels[index2]->geometry());

    QPropertyAnimation *anim2 = new QPropertyAnimation(labels[index2], "geometry");
    anim2->setDuration(500);
    anim2->setStartValue(labels[index2]->geometry());
    anim2->setEndValue(labels[index1]->geometry());

    QLabel *tempLabel = labels[index1];
    labels[index1] = labels[index2];
    labels[index2] = tempLabel;

    // Remove the labels from the layout
    arrayLayout->removeWidget(labels[index1]);
    arrayLayout->removeWidget(labels[index2]);

    // Add the labels back to the layout in the new order
    arrayLayout->insertWidget(index1, labels[index1]);
    arrayLayout->insertWidget(index2, labels[index2]);


    anim1->start(QAbstractAnimation::DeleteWhenStopped);
    anim2->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::initLabels(){
    i = 0;
    j = 1;
    if(j != n){//①下一个检查位置为蓝光
        labels[j]->setStyleSheet("background-color: blue;");
    }
    minIndex = i;
    labels[minIndex]->setStyleSheet("background-color: yellow;");
}
