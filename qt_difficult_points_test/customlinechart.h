// customlinechart.h
#ifndef CUSTOMLINECHART_H
#define CUSTOMLINECHART_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QVector>
#include "quadtreenode.h"

// 定义数据集结构体
struct DataSet {
    QVector<DataPoint> points;
    QColor color;
    QString label;
};

class CustomLineChart : public QWidget
{
    Q_OBJECT
public:
    explicit CustomLineChart(QWidget *parent = nullptr);
    ~CustomLineChart();

    // 添加数据集
    void addDataSet(const DataSet& dataSet);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    // 重新构建四叉树
    void rebuildQuadtree();
    // 绘制坐标轴
    void drawAxes(QPainter& painter);
    // 绘制折线
    void drawLines(QPainter& painter);
    // 绘制数据点提示
    void drawDataPointTip(QPainter& painter);

    QVector<DataSet> m_dataSets;
    bool m_isMouseOver;
    QPoint m_mousePos;
    QuadTreeNode* m_quadtree;
};

#endif // CUSTOMLINECHART_H
