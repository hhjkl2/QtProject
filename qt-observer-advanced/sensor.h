// sensor.h（被观察者：支持自定义类型的传感器）
#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include "temperaturedata.h"  // 包含 TemperatureData 定义

class Sensor : public QObject
{
    Q_OBJECT
public:
    explicit Sensor(QObject *parent = nullptr);
    void updateData(double value);  // 模拟数据更新

signals:
    void dataUpdated(TemperatureData data);  // 信号参数为自定义类型
};

#endif // SENSOR_H
