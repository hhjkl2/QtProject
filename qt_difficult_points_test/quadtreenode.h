// quadtreenode.h
#ifndef QUADTREENODE_H
#define QUADTREENODE_H

#include <QRectF>
#include <QVector>
#include "datapoint.h"

class QuadTreeNode {
public:
    QuadTreeNode(const QRectF& bounds, int capacity);
    ~QuadTreeNode();

    bool insert(const DataPoint& point);
    void query(const QRectF& range, QVector<DataPoint>& foundPoints) const;

private:
    void subdivide();

    QRectF m_bounds;
    int m_capacity;
    QVector<DataPoint> m_points;
    QuadTreeNode* m_northwest;
    QuadTreeNode* m_northeast;
    QuadTreeNode* m_southwest;
    QuadTreeNode* m_southeast;

    // 添加友元声明允许测试类访问私有成员
    friend class TestQuadtree;
};

#endif // QUADTREENODE_H
