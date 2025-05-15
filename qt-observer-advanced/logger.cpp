#include "logger.h"
#include <QDebug>

Logger::Logger(QObject *parent)
    : QObject{parent}
{}

void Logger::logData(TemperatureData data) {
    qDebug() << "[" << data.timestamp << "] 温度：" << data.value << "°C";
}
