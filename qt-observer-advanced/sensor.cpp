// sensor.cpp
#include "sensor.h"
#include <QDateTime>

Sensor::Sensor(QObject *parent) : QObject(parent) {}

void Sensor::updateData(double value) {
    QString ts = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    emit dataUpdated(TemperatureData(value, ts));  // 触发信号
}
