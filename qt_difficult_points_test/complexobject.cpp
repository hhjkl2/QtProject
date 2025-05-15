// complexobject.cpp
#include "complexobject.h"
#include <QDebug>
#include <random> // 随机数头文件

ComplexObject::ComplexObject(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ComplexObject::onTimerTimeout);
}

ComplexObject::~ComplexObject()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }
}

void ComplexObject::startTimer(int interval)
{
    m_timer->start(interval);
}

void ComplexObject::stopTimer()
{
    m_timer->stop();
}

void ComplexObject::onTimerTimeout()
{
    // 创建随机引擎和分布
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(0, 99);

    int random_value = distrib(gen);
    //m_data.append(qrand() % 100);
     m_data.append(random_value);
    emit dataUpdated(m_data);
    qDebug() << "Data updated:" << m_data;
}
