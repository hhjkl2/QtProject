// mediator.h（中介者：转发信号）
#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QObject>
#include "temperaturedata.h"

class Mediator : public QObject
{
    Q_OBJECT
public:
    explicit Mediator(QObject *parent = nullptr);

public slots:
    void onSensorUpdated(TemperatureData data);  // 接收原始信号

signals:
    void dataForwarded(TemperatureData data);  // 转发的信号
};

#endif // MEDIATOR_H
