// complexobject.h
#ifndef COMPLEXOBJECT_H
#define COMPLEXOBJECT_H

#include <QObject>
#include <QTimer>
#include <QVector>

class ComplexObject : public QObject
{
    Q_OBJECT
public:
    explicit ComplexObject(QObject *parent = nullptr);
    ~ComplexObject();

    // 启动定时器
    void startTimer(int interval);

    // 停止定时器
    void stopTimer();

signals:
    // 数据更新信号
    void dataUpdated(const QVector<int> &data);

private slots:
    // 定时器超时槽函数
    void onTimerTimeout();

private:
    QTimer *m_timer;
    QVector<int> m_data;
};

#endif // COMPLEXOBJECT_H
