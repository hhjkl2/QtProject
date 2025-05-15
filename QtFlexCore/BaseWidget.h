// BaseWidget.h（头文件）
#ifndef BASE_WIDGET_H
#define BASE_WIDGET_H

#include <QWidget>
#include "ScalingManager.h"

class BaseWidget : public QWidget {
    Q_OBJECT
public:
    explicit BaseWidget(QWidget* parent = nullptr) : QWidget(parent) {
        connect(&ScalingManager::instance(), &ScalingManager::dpiChanged,
                this, &BaseWidget::reapplyScaling); // 监听 DPI 变化
        applyScaling(); // 初始化缩放
    }

protected:
    // 重写尺寸变化事件（窗口缩放时重新适配）
    void resizeEvent(QResizeEvent* event) override {
        QWidget::resizeEvent(event);
        applyScaling(); // 窗口大小变化时更新布局
    }

private slots:
    void reapplyScaling() {
        applyScaling();
        updateGeometry(); // 触发布局更新
    }

private:
    virtual void applyScaling() = 0; // 子类需实现具体缩放逻辑
};

#endif // BASE_WIDGET_H
