#include <QCoreApplication>
#include <QSystemSemaphore>
#include <QDebug>
#include <QThread>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // 创建或打开信号量（初始资源数1，即互斥锁）
    QSystemSemaphore semaphore("Global\\MySemaphore", 1, QSystemSemaphore::Open);

    // 获取信号量（阻塞直到成功）
    if (!semaphore.acquire()) {
        qDebug() << "[进程A] 获取信号量失败";
        return 1;
    }

    // 访问共享资源
    qDebug() << "[进程A] 正在访问共享资源...";
    QThread::sleep(20); // 模拟耗时操作

    // 释放信号量
    if (!semaphore.release()) {
        qDebug() << "[进程A] 释放信号量失败";
        return 1;
    }

    qDebug() << "[进程A] 操作完成";
    return 0;
}
