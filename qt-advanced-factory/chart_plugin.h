// chart_plugin.h 修改后
#ifndef CHART_PLUGIN_H
#define CHART_PLUGIN_H

#include "ifactory.h"
#include "iproduct.h"
#include <QtCharts>


// chart_plugin.h 修改部分
class ChartProduct : public IProduct {
    Q_OBJECT
    Q_INTERFACES(IProduct)
private:
    QLineSeries* m_series; // 新增成员变量
    QChart* m_chart;        // 新增成员变量
    QChartView* m_view;     // 新增成员变量

public:
    explicit ChartProduct(QObject* parent = nullptr)
        : IProduct(parent), m_series(nullptr), m_chart(nullptr), m_view(nullptr) {}

    QString name() const override { return "ChartPlugin"; }
    QWidget* widget(QWidget* parent) override {
        if (!m_view) { // 确保只创建一次
            m_series = new QLineSeries();
            m_chart = new QChart();
            m_chart->addSeries(m_series);
            m_chart->createDefaultAxes(); // 提前创建坐标轴

            // 初始化坐标轴范围
            m_chart->axisX()->setRange(0, 1);
            m_chart->axisY()->setRange(0, 1);

            m_view = new QChartView(m_chart, parent);
            m_view->setRenderHint(QPainter::Antialiasing);
        }
        return m_view;
    }

    void execute() override {
        if (m_series) {
            m_series->clear(); // 清除旧数据
            // 生成0-1范围内的示例数据（匹配当前坐标轴）
            m_series->append(0.0, 0.6);
            m_series->append(0.25, 0.4);
            m_series->append(0.5, 0.8);
            m_series->append(0.75, 0.5);
            m_series->append(1.0, 0.9);

            // 手动设置坐标轴范围（强制适配0-1）
            m_chart->axisX()->setRange(0, 1);
            m_chart->axisY()->setRange(0, 1);
            m_chart->update();
        }
    }
};

class ChartFactory : public IFactory {
    Q_OBJECT
public:
    // QMetaObject::newInstance()只能调用被Q_INVOKABLE标记的构造函数或默认构造函数。
    Q_INVOKABLE explicit ChartFactory(QObject* parent = nullptr) : IFactory(parent) {} // 新增构造函数

    IProduct* create(QWidget* parent = nullptr) override {
        // 将 QWidget* 转换为 QObject* 传递
        return new ChartProduct(parent ? parent : Q_NULLPTR);
    }
};

// 注册工厂到元工厂
Q_DECLARE_METATYPE(ChartFactory*)

#endif // CHART_PLUGIN_H
