// MainWindow.cpp（源文件）
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ScalingManager.h"
#include "ElasticLayout.h"
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化缩放管理器（在 main 函数中调用更安全）
    ScalingManager::instance().init();

    // 创建中心部件和弹性布局
    QWidget* centralWidget = new QWidget(this);
    ElasticLayout* mainLayout = new ElasticLayout(centralWidget); // 基准边距 16px，间距 12px

    // 标题标签（基准字体 24pt，矢量字体）
    QLabel* titleLabel = new QLabel("跨分辨率适配演示", centralWidget);
    titleLabel->setFont(ScalingManager::instance().scaledFont(titleLabel->font(), 24));
    mainLayout->addWidget(titleLabel);

    // 内容区域（自适应文本框和按钮）
    QTextEdit* textEdit = new QTextEdit(centralWidget);
    textEdit->setMinimumHeight(ScalingManager::instance().scale(150)); // 基准高度 150px
    mainLayout->addWidget(textEdit);

    QPushButton* demoButton = new QPushButton("动态适配按钮", centralWidget);
    demoButton->setFixedSize(
        ScalingManager::instance().scale(120), // 基准宽度 120px
        ScalingManager::instance().scale(40)  // 基准高度 40px
        );
    mainLayout->addWidget(demoButton);

    setCentralWidget(centralWidget);
    setWindowTitle("Qt 跨分辨率适配");
    // 设置初始窗口大小（基准 1280x720，根据缩放系数动态调整）
    resize(
        ScalingManager::instance().scale(1280),
        ScalingManager::instance().scale(720)
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}
