#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QDebug>

// 共享缓冲区配置
const int BufferSize = 3;
int buffer[BufferSize] = {0};
int readPos = 0, writePos = 0;  // 读写指针（需互斥保护）

// 同步原语
QSemaphore empty(BufferSize);  // 空闲位置数
QSemaphore full(0);            // 已填充位置数
QMutex mutex;                  // 保护读写指针

// 生产者线程
class Producer : public QThread {
    void run() override {
        for (int i = 1; i <= 5; ++i) {
            empty.acquire();  // 获取空闲位置
            mutex.lock();     // 保护写指针
            buffer[writePos] = i;
            qDebug() << "生产者写入：" << i << "（位置" << writePos << "）";
            writePos = (writePos + 1) % BufferSize;
            mutex.unlock();   // 释放写指针
            full.release();   // 释放已填充位置
            msleep(500);
        }
    }
};

// 消费者线程
class Consumer : public QThread {
    void run() override {
        for (int i = 1; i <= 5; ++i) {
            full.acquire();   // 获取已填充位置
            mutex.lock();     // 保护读指针
            int value = buffer[readPos];
            qDebug() << "消费者读取：" << value << "（位置" << readPos << "）";
            readPos = (readPos + 1) % BufferSize;
            mutex.unlock();   // 释放读指针
            empty.release();  // 释放空闲位置
            msleep(800);
        }
    }
};

int main() {
    Producer producer;
    Consumer consumer;
    producer.start();
    consumer.start();
    producer.wait();
    consumer.wait();
    qDebug() << "所有任务完成！";
    return 0;
}
