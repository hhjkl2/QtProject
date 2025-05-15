// ScalingManager.h（头文件）
#ifndef SCALING_MANAGER_H
#define SCALING_MANAGER_H

#include <QObject>
#include <QScreen>
#include <QFont>
#include <QSize>

class ScalingManager : public QObject {
    Q_OBJECT
public:
    // 单例获取
    static ScalingManager& instance() {
        static ScalingManager inst;
        return inst;
    }

    // 初始化（在 QApplication 创建后调用）
    void init() {
        QScreen* primaryScreen = qApp->primaryScreen();
        m_dpi = primaryScreen->logicalDotsPerInch();
        m_scaleFactor = m_dpi / 96.0; // 基准 DPI 为 96
    }

    // 获取缩放系数
    double scaleFactor() const { return m_scaleFactor; }

    // 转换基准像素到目标像素（含误差控制）
    int scale(int basePx) const {
        return qRound(basePx * m_scaleFactor); // 四舍五入，误差 ≤ ±1px
    }

    // 转换基准字体大小（点大小）
    QFont scaledFont(const QFont& font, int basePointSize) const {
        QFont scaled = font;
        scaled.setPointSize(qRound(basePointSize * m_scaleFactor));
        return scaled;
    }

signals:
    void dpiChanged(); // DPI 变化时触发 UI 重绘

private:
    double m_scaleFactor = 1.0;
    int m_dpi = 96;
};

#endif // SCALING_MANAGER_H
