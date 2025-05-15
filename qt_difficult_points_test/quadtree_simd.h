// quadtree_simd.h
#ifndef QUADTREE_SIMD_H
#define QUADTREE_SIMD_H

#include <QRectF>
#include <QVector>
#include <xmmintrin.h>
#include <emmintrin.h>
#include "datapoint.h"

class QuadTreeSIMD {
public:
    explicit QuadTreeSIMD(const QRectF& bounds, int capacity = 4);
    ~QuadTreeSIMD();

    bool insert(const DataPoint& point);
    void query(const QRectF& range, QVector<DataPoint>& results) const;
    void clear();

private:
    struct Node {
        QRectF bounds;            // 范围
        QVector<float> points_x;  // x坐标数组
        QVector<float> points_y;  // y坐标数组
        Node* children[4] = {nullptr};  // NW, NE, SW, SE
        int capacity;

        Node(const QRectF& b, int cap) : bounds(b), capacity(cap) {}
    };

    // 内存块管理结构
    struct MemoryChunk {
        Node* nodes;          // 内存块指针
        size_t size;          // 块内节点总数
        size_t used;          // 已使用数量
        MemoryChunk* next;    // 下一个块

        MemoryChunk(size_t chunkSize);
        ~MemoryChunk();
    };

    // 动态内存池
    MemoryChunk* chunkList = nullptr;
    const size_t chunkSize = 10000;  // 每个块初始容量
    Node* root;

    // 内存管理
    Node* allocateNode();
    void releaseChunks();

    // 核心逻辑
    bool insert(Node* node, float x, float y);
    void subdivide(Node* node);
    void query(const Node* node, const QRectF& range, QVector<DataPoint>& results) const;

    // SIMD工具函数
    static __m128 loadBoundsMin(const QRectF& rect);
    static __m128 loadBoundsMax(const QRectF& rect);
    static bool pointInBoundsSIMD(__m128 point, __m128 boundsMin, __m128 boundsMax);
};

#endif // QUADTREE_SIMD_H
