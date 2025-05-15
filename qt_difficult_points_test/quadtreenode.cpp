// quadtreenode.cpp
#include "quadtreenode.h"
#include <QDebug>

QuadTreeNode::QuadTreeNode(const QRectF& bounds, int capacity)
    : m_bounds(bounds), m_capacity(capacity), m_northwest(nullptr), m_northeast(nullptr), m_southwest(nullptr), m_southeast(nullptr)
{
}

QuadTreeNode::~QuadTreeNode()
{
    delete m_northwest;
    delete m_northeast;
    delete m_southwest;
    delete m_southeast;
}

bool QuadTreeNode::insert(const DataPoint& point)
{
    if (!m_bounds.contains(point.x, point.y)) {
        return false;
    }

    if (m_points.size() < m_capacity) {
        m_points.append(point);
        return true;
    }

    if (m_northwest == nullptr) {
        subdivide();
    }

    if (m_northwest->insert(point)) return true;
    if (m_northeast->insert(point)) return true;
    if (m_southwest->insert(point)) return true;
    if (m_southeast->insert(point)) return true;

    return false;
}

void QuadTreeNode::subdivide()
{
    double x = m_bounds.x();
    double y = m_bounds.y();
    double w = m_bounds.width() / 2;
    double h = m_bounds.height() / 2;

    m_northwest = new QuadTreeNode(QRectF(x, y, w, h), m_capacity);
    m_northeast = new QuadTreeNode(QRectF(x + w, y, w, h), m_capacity);
    m_southwest = new QuadTreeNode(QRectF(x, y + h, w, h), m_capacity);
    m_southeast = new QuadTreeNode(QRectF(x + w, y + h, w, h), m_capacity);
}

void QuadTreeNode::query(const QRectF& range, QVector<DataPoint>& foundPoints) const
{
    //qDebug() << "执行query";
    if (!m_bounds.intersects(range)) {
        //qDebug() << "该区域不包含range";
        return;
    }

    for (const auto& point : m_points) {
        //qDebug() << point.x << point.y;
        if (range.contains(point.x, point.y)) {
            //qDebug() << point.x << point.y;
            foundPoints.append(point);
        }
    }

    if (m_northwest != nullptr) {
        m_northwest->query(range, foundPoints);
        m_northeast->query(range, foundPoints);
        m_southwest->query(range, foundPoints);
        m_southeast->query(range, foundPoints);
    }
}
