// quadtreenode2.cpp
#include "quadtreenode2.h"
#include <QDebug>

QuadTreeNode2::QuadTreeNode2(const QRectF& bounds, int capacity)
    : m_bounds(bounds), m_capacity(capacity), m_northwest(nullptr), m_northeast(nullptr), m_southwest(nullptr), m_southeast(nullptr)
{
}

QuadTreeNode2::~QuadTreeNode2()
{
    delete m_northwest;
    delete m_northeast;
    delete m_southwest;
    delete m_southeast;
}

bool QuadTreeNode2::insert(const DataPoint& point) {
    if (!m_bounds.contains(point.x, point.y)) {
        return false;
    }

    // 如果未超容，直接存储
    if (m_points.size() < m_capacity) {
        m_points.append(point);
        return true;
    }

    // 需要分裂时处理数据迁移
    if (m_northwest == nullptr) {
        subdivide(); // 创建子节点

        // 将父节点现有数据迁移到子节点
        for (const auto& p : m_points) {
            bool inserted =
                m_northwest->insert(p) ||
                m_northeast->insert(p) ||
                m_southwest->insert(p) ||
                m_southeast->insert(p);
            Q_ASSERT_X(inserted, "insert", "数据必须属于某个子节点");
        }
        m_points.clear(); // 清空父节点数据
    }

    // 插入新数据到子节点
    return (m_northwest->insert(point) ||
            m_northeast->insert(point) ||
            m_southwest->insert(point) ||
            m_southeast->insert(point));
}

void QuadTreeNode2::subdivide()
{
    double x = m_bounds.x();
    double y = m_bounds.y();
    double w = m_bounds.width() / 2;
    double h = m_bounds.height() / 2;

    m_northwest = new QuadTreeNode2(QRectF(x, y, w, h), m_capacity);
    m_northeast = new QuadTreeNode2(QRectF(x + w, y, w, h), m_capacity);
    m_southwest = new QuadTreeNode2(QRectF(x, y + h, w, h), m_capacity);
    m_southeast = new QuadTreeNode2(QRectF(x + w, y + h, w, h), m_capacity);
}

void QuadTreeNode2::query(const QRectF& range, QVector<DataPoint>& foundPoints) const
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
