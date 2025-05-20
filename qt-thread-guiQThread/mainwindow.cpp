#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    progressBar = new QProgressBar(this);
    setCentralWidget(new QWidget(this));
    centralWidget()->setLayout(new QVBoxLayout);
    centralWidget()->layout()->addWidget(progressBar);

    worker = new WorkerThread(this);
    connect(worker, &WorkerThread::progressUpdated, progressBar, &QProgressBar::setValue);
    connect(worker, &QThread::finished, this, [this]() {
        progressBar->setFormat("完成！");
    });
    worker->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
