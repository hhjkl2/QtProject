// quadtreenode2.h
#ifndef QUADTREENODE2_H
#define QUADTREENODE2_H

#include <QRectF>
#include <QVector>
#include "datapoint.h"

class QuadTreeNode2 {
public:
    QuadTreeNode2(const QRectF& bounds, int capacity);
    ~QuadTreeNode2();

    bool insert(const DataPoint& point);
    void query(const QRectF& range, QVector<DataPoint>& foundPoints) const;

private:
    void subdivide();

    QRectF m_bounds;
    int m_capacity;
    QVector<DataPoint> m_points;
    QuadTreeNode2* m_northwest;
    QuadTreeNode2* m_northeast;
    QuadTreeNode2* m_southwest;
    QuadTreeNode2* m_southeast;

    // 添加友元声明允许测试类访问私有成员
    friend class TestQuadtree;
};

#endif // QUADTREENODE2_H
