// ElasticLayout.h（头文件）
#ifndef ELASTIC_LAYOUT_H
#define ELASTIC_LAYOUT_H

#include <QVBoxLayout>
#include "ScalingManager.h"

class ElasticLayout : public QVBoxLayout {
public:
    explicit ElasticLayout(QWidget* parent = nullptr, int baseMargin = 16, int baseSpacing = 12)
        : QVBoxLayout(parent), m_baseMargin(baseMargin), m_baseSpacing(baseSpacing) {
        updateScaling(); // 初始化布局参数
        connect(&ScalingManager::instance(), &ScalingManager::dpiChanged,
                this, &ElasticLayout::updateScaling); // 监听 DPI 变化
    }

private:
    void updateScaling() {
        auto& scaling = ScalingManager::instance();
        setContentsMargins(
            scaling.scale(m_baseMargin),  // 左
            scaling.scale(m_baseMargin),  // 上
            scaling.scale(m_baseMargin),  // 右
            scaling.scale(m_baseMargin)   // 下
            );
        setSpacing(scaling.scale(m_baseSpacing)); // 控件间距
    }

    int m_baseMargin; // 基准边距（px）
    int m_baseSpacing; // 基准间距（px）
};

#endif // ELASTIC_LAYOUT_H
