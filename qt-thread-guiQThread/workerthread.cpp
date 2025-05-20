#include "workerthread.h"

WorkerThread::WorkerThread(QObject *parent) : QThread(parent) {}

void WorkerThread::run() {
    for (int i = 0; i <= 100; ++i) {
        emit progressUpdated(i);
        QThread::msleep(50); // 模拟耗时操作
    }
}
