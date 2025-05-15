// main.cpp（跨线程更新属性）
#include <QCoreApplication>
#include <QThread>
#include "logger.h"
#include "sensor.h"
#include "mediator.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    qRegisterMetaType<TemperatureData>("TemperatureData"); // 注册元类型

    Sensor sensor;
    Mediator mediator;
    Logger logger;

    // 传感器→中介者→日志
    QObject::connect(&sensor, &Sensor::dataUpdated,
                     &mediator, &Mediator::onSensorUpdated);
    QObject::connect(&mediator, &Mediator::dataForwarded,
                     &logger, &Logger::logData);

    sensor.updateData(28.0);
    return a.exec();
}
