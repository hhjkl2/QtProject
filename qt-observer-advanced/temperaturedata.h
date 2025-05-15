#ifndef TEMPERATUREDATA_H
#define TEMPERATUREDATA_H

// 自定义类型（需注册元类型）
#include <QMetaType>

struct TemperatureData {
    double value;
    QString timestamp;
    TemperatureData(double v, const QString &ts) : value(v), timestamp(ts) {}
};
Q_DECLARE_METATYPE(TemperatureData)  // 声明元类型

#endif // TEMPERATUREDATA_H
