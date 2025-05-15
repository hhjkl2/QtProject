// device.h（支持属性的设备类）
#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include "temperaturedata.h"

class Device : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double temperature READ temperature NOTIFY temperatureChanged)  // 声明属性
public:
    explicit Device(QObject *parent = nullptr);
    double temperature() const;  // 属性读取函数

public slots:
    void setTemperature(double value);  // 修改属性的槽

signals:
    void temperatureChanged(TemperatureData value);  // 属性变化信号

private:
    double m_temperature = 0.0;
};

#endif // DEVICE_H
