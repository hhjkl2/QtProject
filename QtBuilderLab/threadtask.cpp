#include "threadtask.h"
#include <QDebug>

void createBackgroundTask(){
    ThreadTask task = ThreadTaskBuilder("DataCalculationTask")
    .setPriority(QThread::HighPriority)
        .setTask([]() {
            // 模拟耗时操作（如大数据计算）
            for (int i = 0; i <= 100; ++i) {
                QThread::msleep(50); // 模拟计算
                // 触发进度回调（线程安全）
                // 实际需通过信号槽跨线程传递，此处简化处理
            }
        })
        .onStart([]() { qDebug() << "任务开始"; })
        .onFinish([]() { qDebug() << "任务完成"; })
        .onProgress([](const QString& msg) { qDebug() << "进度：" << msg; })
        .build();

    task.start(); // 启动任务
}
