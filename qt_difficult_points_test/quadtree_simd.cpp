#include "quadtree_simd.h"
#include <cassert>
#include <cstdlib>
#include <QDebug>

// MemoryChunk实现
QuadTreeSIMD::MemoryChunk::MemoryChunk(size_t chunkSize)
    : size(chunkSize), used(0), next(nullptr) {
    nodes = static_cast<Node*>(_aligned_malloc(chunkSize * sizeof(Node), 16));
}

QuadTreeSIMD::MemoryChunk::~MemoryChunk() {
    _aligned_free(nodes);
}

// QuadTreeSIMD核心实现
QuadTreeSIMD::QuadTreeSIMD(const QRectF& bounds, int capacity) {
    root = allocateNode();
    new (root) Node(bounds, capacity);  // 原位构造
}

QuadTreeSIMD::~QuadTreeSIMD() {
    clear();
    releaseChunks();
}

QuadTreeSIMD::Node* QuadTreeSIMD::allocateNode() {
    // 遍历现有块寻找可用位置
    MemoryChunk* current = chunkList;
    while (current) {
        if (current->used < current->size) {
            Node* node = &current->nodes[current->used++];
            return node;
        }
        current = current->next;
    }

    // 所有块已满，创建新块
    MemoryChunk* newChunk = new MemoryChunk(chunkSize);
    newChunk->next = chunkList;
    chunkList = newChunk;

    // 返回新块第一个节点
    Node* node = &newChunk->nodes[newChunk->used++];
    return node;
}

void QuadTreeSIMD::releaseChunks() {
    MemoryChunk* current = chunkList;
    while (current) {
        MemoryChunk* next = current->next;
        delete current;  // 触发MemoryChunk析构
        current = next;
    }
    chunkList = nullptr;
}

bool QuadTreeSIMD::insert(const DataPoint& point) {
    return insert(root, point.x, point.y);
}

bool QuadTreeSIMD::insert(Node* node, float x, float y) {
    // qDebug() << "执行insert";
    // SIMD边界检查
    const __m128 pointVec = _mm_set_ps(0, 0, y, x);
    const __m128 boundsMin = loadBoundsMin(node->bounds);
    const __m128 boundsMax = loadBoundsMax(node->bounds);

    if (!pointInBoundsSIMD(pointVec, boundsMin, boundsMax)) {
        // qDebug() << "点不在范围内";
        return false;
    }

    //qDebug() << "node->points_x.size() = " << node->points_x.size();
    if (node->points_x.size() < node->capacity) {
        node->points_x.append(x);
        node->points_y.append(y);
        return true;
    }

    if (!node->children[0]) {
        subdivide(node);
        // qDebug() << "执行迁移数据";
        // 迁移数据
        // qDebug() << "node->points_x.size() = " << node->points_x.size();
        const size_t count = node->points_x.size();
        for (size_t i = 0; i < count; ++i) {
            const float px = node->points_x[i];
            const float py = node->points_y[i];
            for (int j = 0; j < 4; ++j) {
                if (insert(node->children[j], px, py)) break;
            }
        }
        node->points_x.clear();
        node->points_y.clear();
        // qDebug() << "执行完迁移数据";
    }

    for (int i = 0; i < 4; ++i) {
        if (insert(node->children[i], x, y)) return true;
    }
    return false;
}

void QuadTreeSIMD::subdivide(Node* node) {
    // qDebug() << "执行subdivide";
    const float x = node->bounds.x();
    const float y = node->bounds.y();
    const float w = node->bounds.width() / 2;
    const float h = node->bounds.height() / 2;

    node->children[0] = allocateNode();
    new (node->children[0]) Node(QRectF(x, y, w, h), node->capacity);

    node->children[1] = allocateNode();
    new (node->children[1]) Node(QRectF(x + w, y, w, h), node->capacity);

    node->children[2] = allocateNode();
    new (node->children[2]) Node(QRectF(x, y + h, w, h), node->capacity);

    node->children[3] = allocateNode();
    new (node->children[3]) Node(QRectF(x + w, y + h, w, h), node->capacity);
    // qDebug() << "执行完subdivide";
}

void QuadTreeSIMD::query(const QRectF& range, QVector<DataPoint>& results) const {
    query(root, range, results);
}

void QuadTreeSIMD::query(const Node* node, const QRectF& range, QVector<DataPoint>& results) const {
    // SIMD边界相交检测
    const __m128 rangeMin = loadBoundsMin(range);
    const __m128 rangeMax = loadBoundsMax(range);
    const __m128 nodeMin = loadBoundsMin(node->bounds);
    const __m128 nodeMax = loadBoundsMax(node->bounds);

    const __m128 cmp1 = _mm_cmpge_ps(nodeMax, rangeMin);
    const __m128 cmp2 = _mm_cmpge_ps(rangeMax, nodeMin);
    const __m128 cmpResult = _mm_and_ps(cmp1, cmp2);

    if ((_mm_movemask_ps(cmpResult) & 0x3) != 0x3) return;

    // 批量检查点
    const size_t count = node->points_x.size();
    for (size_t i = 0; i < count; i += 4) {
        __m128 xVec = _mm_load_ps(&node->points_x[i]);
        __m128 yVec = _mm_load_ps(&node->points_y[i]);

        __m128 xMask = _mm_and_ps(
            _mm_cmpge_ps(xVec, _mm_set1_ps(range.x())),
            _mm_cmple_ps(xVec, _mm_set1_ps(range.right()))
            );
        __m128 yMask = _mm_and_ps(
            _mm_cmpge_ps(yVec, _mm_set1_ps(range.y())),
            _mm_cmple_ps(yVec, _mm_set1_ps(range.bottom()))
            );
        __m128 mask = _mm_and_ps(xMask, yMask);

        int bits = _mm_movemask_ps(mask);
        for (int j = 0; j < 4; ++j) {
            if (bits & (1 << j)) {
                results.append(DataPoint(
                    node->points_x[i + j],
                    node->points_y[i + j]
                    ));
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (node->children[i]) query(node->children[i], range, results);
    }
}

// SIMD工具函数
__m128 QuadTreeSIMD::loadBoundsMin(const QRectF& rect) {
    return _mm_set_ps(0, 0, static_cast<float>(rect.y()), static_cast<float>(rect.x()));
}

__m128 QuadTreeSIMD::loadBoundsMax(const QRectF& rect) {
    return _mm_set_ps(0, 0, static_cast<float>(rect.bottom()), static_cast<float>(rect.right()));
}

bool QuadTreeSIMD::pointInBoundsSIMD(__m128 point, __m128 boundsMin, __m128 boundsMax) {
    __m128 cmpMin = _mm_cmpge_ps(point, boundsMin);
    __m128 cmpMax = _mm_cmple_ps(point, boundsMax);
    __m128 result = _mm_and_ps(cmpMin, cmpMax);
    return (_mm_movemask_ps(result) & 0x3) == 0x3;
}

void QuadTreeSIMD::clear() {
    releaseChunks();
    root = allocateNode();
    new (root) Node(root->bounds, root->capacity);
}
