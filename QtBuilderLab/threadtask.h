#ifndef THREADTASK_H
#define THREADTASK_H

#include <QThreadPool>
#include <QThread>
#include <QRunnable>
#include <QObject>
#include <QMutex>
#include <QWaitCondition>

// 产品类：可运行的线程任务（含线程、任务、回调）
class ThreadTask {
public:
    // 添加构造函数
    ThreadTask(QThread* thread, QRunnable* runnable,
               std::function<void()> onStart,
               std::function<void()> onFinish,
               std::function<void(const QString&)> onProgress)
        : m_thread(thread), m_runnable(runnable),
        m_onStart(onStart), m_onFinish(onFinish),
        m_onProgress(onProgress) {}

    void start() {
        m_thread->start();
        m_runnable->setAutoDelete(false); // 手动管理生命周期（与线程绑定）
        QThreadPool::globalInstance()->start(m_runnable);
    }

private:
    friend class ThreadTaskBuilder; // 允许建造者访问私有成员
    QThread* m_thread = nullptr;
    QRunnable* m_runnable = nullptr;
    std::function<void()> m_onStart;    // 任务启动回调
    std::function<void()> m_onFinish;   // 任务完成回调
    std::function<void(const QString&)> m_onProgress; // 进度更新回调
};

// 单独定义的TaskRunnable类（必须包含Q_OBJECT宏）
class TaskRunnable : public QObject, public QRunnable  {
    Q_OBJECT
public:
    TaskRunnable(std::function<void()> task,
                 std::function<void()> onStart,
                 std::function<void()> onFinish,
                 std::function<void(const QString&)> onProgress)
        : QObject(nullptr), // 显式初始化QObject
        m_task(task), m_onStart(onStart), m_onFinish(onFinish), m_onProgress(onProgress) {
        setAutoDelete(false); // 由线程管理生命周期
    }

    void run() override {
        if (m_onStart) m_onStart(); // 触发启动回调

        // 模拟带进度更新的任务
        for (int i = 0; i <= 100; ++i) {
            QThread::msleep(50);
            emit progressUpdated(QString("已完成 %1%").arg(i)); // 触发进度信号
        }

        m_task(); // 执行任务逻辑
        if (m_onFinish) m_onFinish(); // 触发完成回调
    }

signals:
    void progressUpdated(const QString& msg); // 用于线程间进度通知

private:
    std::function<void()> m_task;
    std::function<void()> m_onStart;
    std::function<void()> m_onFinish;
    std::function<void(const QString&)> m_onProgress;

public:
    std::function<void(const QString&)> getOnProgress(){
        return m_onProgress;
    }
};

// 建造者类：线程任务配置（支持线程优先级、回调绑定）
class ThreadTaskBuilder {
public:
    explicit ThreadTaskBuilder(const QString& taskName) : m_taskName(taskName) {}

    // 设置线程优先级
    ThreadTaskBuilder& setPriority(QThread::Priority priority) {
        m_priority = priority;
        return *this;
    }

    // 绑定任务逻辑（必须）
    ThreadTaskBuilder& setTask(std::function<void()> task) {
        m_task = task;
        return *this;
    }

    // 绑定启动回调
    ThreadTaskBuilder& onStart(std::function<void()> callback) {
        m_onStart = callback;
        return *this;
    }

    // 绑定完成回调
    ThreadTaskBuilder& onFinish(std::function<void()> callback) {
        m_onFinish = callback;
        return *this;
    }

    // 绑定进度回调（线程安全）
    ThreadTaskBuilder& onProgress(std::function<void(const QString&)> callback) {
        m_onProgress = callback;
        return *this;
    }

    // 构建线程任务（线程安全）
    ThreadTask build() {
        QThread* thread = new QThread;
        thread->setObjectName(m_taskName);
        thread->setPriority(m_priority);

        // 关键修改：明确使用 TaskRunnable* 类型
        TaskRunnable* runnable = new TaskRunnable(m_task, m_onStart, m_onFinish, m_onProgress);


        // 连接进度信号到回调
        QObject::connect(runnable, &TaskRunnable::progressUpdated,
                         runnable, // 添加上下文对象(设置Qt::ConnectionType时必须提供上下文对象，否则可以省略)
                         [runnable](const QString& msg) {
                             if (runnable->getOnProgress()) runnable->getOnProgress()(msg);
                         },Qt::QueuedConnection);

        // 线程结束时清理资源
        QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);
        QObject::connect(thread, &QThread::finished, runnable, &QObject::deleteLater);

        return ThreadTask(thread, runnable, m_onStart, m_onFinish, m_onProgress);
    }

private:
    QString m_taskName;
    QThread::Priority m_priority = QThread::NormalPriority;
    std::function<void()> m_task;
    std::function<void()> m_onStart;
    std::function<void()> m_onFinish;
    std::function<void(const QString&)> m_onProgress;
};

// 使用示例（后台数据计算任务）
void createBackgroundTask();

#endif // THREADTASK_H
