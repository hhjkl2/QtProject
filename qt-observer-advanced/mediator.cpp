#include "mediator.h"
#include <QDebug>

Mediator::Mediator(QObject *parent)
    : QObject{parent}
{}

void Mediator::onSensorUpdated(TemperatureData data) {
    qDebug() << "中介者接收到数据，转发中...";
    emit dataForwarded(data);  // 转发信号
}
