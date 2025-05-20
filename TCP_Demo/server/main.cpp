#include <QCoreApplication>
#include <QSystemSemaphore>
#include <QDebug>
#include <QThread>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // 必须使用相同的信号量名
    QSystemSemaphore semaphore("Global\\MySemaphore", 1, QSystemSemaphore::Open);

    if (!semaphore.acquire()) {
        qDebug() << "[进程B] 获取信号量失败";
        return 1;
    }

    qDebug() << "[进程B] 正在访问共享资源...";
    QThread::sleep(5); // 模拟耗时操作

    if (!semaphore.release()) {
        qDebug() << "[进程B] 释放信号量失败";
        return 1;
    }

    qDebug() << "[进程B] 操作完成";
    return 0;
}
