// device.cpp
#include "device.h"
#include <QDateTime>

Device::Device(QObject *parent)
    : QObject{parent}
{}

double Device::temperature() const { return m_temperature; }

void Device::setTemperature(double value) {
    if (m_temperature != value) {
        m_temperature = value;
        QString timestamp = QDateTime::currentDateTime().toString();
        emit temperatureChanged(TemperatureData(value, timestamp));  // 触发属性变化信号
    }
}
