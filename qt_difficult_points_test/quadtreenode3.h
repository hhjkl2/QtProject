// quadtreenode3.h
#ifndef QUADTREENODE3_H
#define QUADTREENODE3_H

#include <QRectF>
#include <QVector>
#include "datapoint.h"
#include <xmmintrin.h> // 引入SIMD指令集头文件

class QuadTreeNode3 {
public:
    QuadTreeNode3(const QRectF& bounds, int capacity);
    ~QuadTreeNode3();

    bool insert(const DataPoint& point);
    void query(const QRectF& range, QVector<DataPoint>& foundPoints) const;

private:
    void subdivide();

    QRectF m_bounds;
    int m_capacity;
    QVector<DataPoint> m_points;
    QuadTreeNode3* m_northwest;
    QuadTreeNode3* m_northeast;
    QuadTreeNode3* m_southwest;
    QuadTreeNode3* m_southeast;

    // 添加友元声明允许测试类访问私有成员
    friend class TestQuadtree;
};

#endif // QUADTREENODE3_H
