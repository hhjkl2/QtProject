// logger.h（观察者：日志记录器）
#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include "temperaturedata.h"

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);

signals:
public slots:
    void logData(TemperatureData data);  // 槽函数接收自定义类型
};

#endif // LOGGER_H
