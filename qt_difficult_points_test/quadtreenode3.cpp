// quadtreenode3.cpp
#include "quadtreenode3.h"
#include <QDebug>

QuadTreeNode3::QuadTreeNode3(const QRectF& bounds, int capacity)
    : m_bounds(bounds), m_capacity(capacity), m_northwest(nullptr), m_northeast(nullptr), m_southwest(nullptr), m_southeast(nullptr)
{
}

QuadTreeNode3::~QuadTreeNode3()
{
    delete m_northwest;
    delete m_northeast;
    delete m_southwest;
    delete m_southeast;
}

bool QuadTreeNode3::insert(const DataPoint& point) {
    __m128 pointData = _mm_set_ps(0.0f, 0.0f, static_cast<float>(point.y), static_cast<float>(point.x));
    __m128 boundsMin = _mm_set_ps(0.0f, 0.0f, static_cast<float>(m_bounds.y()), static_cast<float>(m_bounds.x()));
    __m128 boundsMax = _mm_set_ps(0.0f, 0.0f, static_cast<float>(m_bounds.y() + m_bounds.height()), static_cast<float>(m_bounds.x() + m_bounds.width()));

    __m128 cmpMin = _mm_cmpge_ps(pointData, boundsMin);
    __m128 cmpMax = _mm_cmple_ps(pointData, boundsMax);
    __m128 cmpResult = _mm_and_ps(cmpMin, cmpMax);

    //低2位均为1，说明在范围内
    if ((_mm_movemask_ps(cmpResult) & 0x3) != 0x3) {
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

void QuadTreeNode3::subdivide()
{
    double x = m_bounds.x();
    double y = m_bounds.y();
    double w = m_bounds.width() / 2;
    double h = m_bounds.height() / 2;

    m_northwest = new QuadTreeNode3(QRectF(x, y, w, h), m_capacity);
    m_northeast = new QuadTreeNode3(QRectF(x + w, y, w, h), m_capacity);
    m_southwest = new QuadTreeNode3(QRectF(x, y + h, w, h), m_capacity);
    m_southeast = new QuadTreeNode3(QRectF(x + w, y + h, w, h), m_capacity);
}

void QuadTreeNode3::query(const QRectF& range, QVector<DataPoint>& foundPoints) const
{
    __m128 rangeMin = _mm_set_ps(0.0f, 0.0f, static_cast<float>(range.y()), static_cast<float>(range.x()));
    __m128 rangeMax = _mm_set_ps(0.0f, 0.0f, static_cast<float>(range.y() + range.height()), static_cast<float>(range.x() + range.width()));
    __m128 boundsMin = _mm_set_ps(0.0f, 0.0f, static_cast<float>(m_bounds.y()), static_cast<float>(m_bounds.x()));
    __m128 boundsMax = _mm_set_ps(0.0f, 0.0f, static_cast<float>(m_bounds.y() + m_bounds.height()), static_cast<float>(m_bounds.x() + m_bounds.width()));

    // 相交逻辑判断
    __m128 cmp1 = _mm_cmpge_ps(boundsMax, rangeMin);
    __m128 cmp2 = _mm_cmpge_ps(rangeMax, boundsMin);
    __m128 cmpResult = _mm_and_ps(cmp1, cmp2);

    if ((_mm_movemask_ps(cmpResult) & 0x3) != 0x3) {
        //qDebug() << "该区域不与range相交";
        return;
    }

    for (const auto& point : m_points) {
        __m128 pointData = _mm_set_ps(0.0f, 0.0f, static_cast<float>(point.y), static_cast<float>(point.x));
        __m128 pointCmpMin = _mm_cmpge_ps(pointData, rangeMin);
        __m128 pointCmpMax = _mm_cmple_ps(pointData, rangeMax);
        __m128 pointCmpResult = _mm_and_ps(pointCmpMin, pointCmpMax);

        if ((_mm_movemask_ps(pointCmpResult) & 0x3) == 0x3) {
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
