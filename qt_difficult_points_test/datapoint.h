//datapoint.h
#ifndef DATAPOINT_H
#define DATAPOINT_H

// 内存对齐的DataPoint结构
struct alignas(16) DataPoint {
    float x;
    float y;
    DataPoint(float x = 0, float y = 0) : x(x), y(y) {}
};

#endif // DATAPOINT_H
