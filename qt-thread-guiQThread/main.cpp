#include <QCoreApplication>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include <QList>

QMutex mutex;          // 互斥锁，保护共享队列
QWaitCondition notEmpty; // 条件变量，等待队列非空
QList<int> queue;       // 共享数据队列

// 生产者线程
class Producer : public QThread {
    void run() override {
        for (int i = 0; i < 5; ++i) {
            mutex.lock();
            queue.append(i);
            qDebug() << "生产者添加：" << i;
            notEmpty.wakeOne(); // 唤醒一个消费者
            mutex.unlock();
            QThread::msleep(500); // 模拟生产耗时
        }
    }
};

// 消费者线程
class Consumer : public QThread {
    void run() override {
        for (int i = 0; i < 5; ++i) {
            mutex.lock();
            while (queue.isEmpty()) {
                notEmpty.wait(&mutex); // 等待队列非空，自动释放锁
            }
            int value = queue.takeFirst();
            qDebug() << "消费者取出：" << value;
            mutex.unlock();
            QThread::msleep(300); // 模拟消费耗时
        }
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Producer producer;
    Consumer consumer;
    producer.start();
    consumer.start();
    producer.wait(); // 等待生产者结束
    consumer.wait(); // 等待消费者结束
    return a.exec();
}
