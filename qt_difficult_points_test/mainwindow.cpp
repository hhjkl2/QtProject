#include "mainwindow.h"
#include <QVBoxLayout>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    customLineChart = new CustomLineChart(this);

    // 创建数据集
    DataSet dataSet1;
    dataSet1.color = Qt::red;
    dataSet1.label = "Data Set 1";
    dataSet1.points = {{0.1, 0.2}, {0.2, 0.4}, {0.3, 0.6}, {0.4, 0.8}, {0.5, 0.7}};

    DataSet dataSet2;
    dataSet2.color = Qt::blue;
    dataSet2.label = "Data Set 2";
    dataSet2.points = {{0.1, 0.8}, {0.2, 0.6}, {0.3, 0.4}, {0.4, 0.2}, {0.5, 0.3}};

    // 添加数据集到图表
    customLineChart->addDataSet(dataSet1);
    customLineChart->addDataSet(dataSet2);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget());
    layout->addWidget(customLineChart);
}

MainWindow::~MainWindow()
{
    delete ui;
}
