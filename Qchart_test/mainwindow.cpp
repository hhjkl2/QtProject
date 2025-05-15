// mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    distribution(-0.2, 0.2)
{
    ui->setupUi(this);

    dataBuffer.resize(100); // 预分配100个点
    for(int i=0; i<100; i++){
        dataBuffer[i] = QPointF(i, 0); // 初始值设为0
    }

    // 初始化图表
    chart = new QChart();
    series = new QLineSeries();
    chart->addSeries(series);

    // 配置坐标轴
    QValueAxis *xAxis = new QValueAxis();
    xAxis->setRange(0, 100);
    xAxis->setTitleText("时间（帧）");
    QValueAxis *yAxis = new QValueAxis();
    yAxis->setRange(-1, 1);
    yAxis->setTitleText("幅值");
    chart->setAxisX(xAxis, series);
    chart->setAxisY(yAxis, series);

    // 图表样式设置
    chart->legend()->hide();
    chart->setTheme(QChart::ChartThemeDark);

    // 创建视图并设置交互
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setRubberBand(QChartView::HorizontalRubberBand); // 水平缩放
    setCentralWidget(chartView);
    resize(800, 600);

    // 启动定时器
    QTimer *dataTimer = new QTimer(this);
    connect(dataTimer, &QTimer::timeout, this, &MainWindow::updateData);
    dataTimer->start(100);
}

void MainWindow::updateData()
{
    // 生成新数据点
    float value = qSin(writeIndex * 0.1) + distribution(*QRandomGenerator::global());

    // 第一阶段：从0到99逐步追加
    if(isFirstPass) {
        dataBuffer[writeIndex] = QPointF(writeIndex, value);

        // 仅显示已填充部分
        QVector<QPointF> currentData(writeIndex + 1);
        std::copy(dataBuffer.begin(), dataBuffer.begin() + writeIndex + 1, currentData.begin());
        series->replace(currentData);

        if(++writeIndex >= 100) {
            isFirstPass = false;
            writeIndex = 0;
            series->setColor(Qt::red); // 进入覆盖阶段后变色
        }
    }
    // 第二阶段：循环覆盖+断点处理
    else {
        qDebug() << "writeIndex:" << writeIndex;
        dataBuffer[writeIndex] = QPointF(writeIndex, value);

        // 构建含断点的数据序列
        QVector<QPointF> displayData;
        displayData.reserve(101); // 预分配空间

        // 添加新数据段（当前写入位置之后的部分）
        for(int i=writeIndex; i<100; i++) {
            displayData << dataBuffer[i];
        }

        // 插入无效点实现断线
        displayData << QPointF(qQNaN(), qQNaN());

        // 添加旧数据段（当前写入位置之前的部分）
        for(int i=0; i<writeIndex; i++) {
            displayData << dataBuffer[i];
        }

        series->replace(displayData);
        writeIndex = (writeIndex + 1) % 100;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
