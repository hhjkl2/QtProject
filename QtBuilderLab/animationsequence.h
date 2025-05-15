#ifndef ANIMATIONSEQUENCE_H
#define ANIMATIONSEQUENCE_H

#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QWidget>

// 产品类：动画组（支持串行/并行）
class AnimationSequence {
public:
    // 添加构造函数
    explicit AnimationSequence(QAbstractAnimation* group) : m_group(group) {}

    void start() { m_group->start(QAbstractAnimation::DeleteWhenStopped); }

private:
    friend class AnimationBuilder; // 允许建造者访问私有成员
    QAbstractAnimation* m_group = nullptr;
};

// 建造者类：动画组配置（支持链式调用+类型安全）
class AnimationBuilder {
public:
    explicit AnimationBuilder(QWidget* target) : m_target(target) {}

    // 添加属性动画（链式调用）
    AnimationBuilder& addPropertyAnim(const QString& prop, const QVariant& start,
                                      const QVariant& end, int duration = 300) {
        QPropertyAnimation* anim = new QPropertyAnimation(m_target, prop.toUtf8());
        anim->setStartValue(start);
        anim->setEndValue(end);
        anim->setDuration(duration);
        m_anims.append(anim);
        return *this;
    }

    // 构建串行动画组
    AnimationSequence buildSequential() {
        QSequentialAnimationGroup* group = new QSequentialAnimationGroup;
        for (auto anim : m_anims) group->addAnimation(anim);
        return AnimationSequence(group);
    }

    // 构建并行动画组
    AnimationSequence buildParallel() {
        QParallelAnimationGroup* group = new QParallelAnimationGroup;
        for (auto anim : m_anims) group->addAnimation(anim);
        return AnimationSequence(group);
    }

private:
    QWidget* m_target;
    QList<QPropertyAnimation*> m_anims;
};

// 使用示例（窗口淡入+缩放动画）
void createWindowAnimation(QWidget* window) {
    AnimationSequence anim = AnimationBuilder(window)
    .addPropertyAnim("windowOpacity", 0.0, 1.0, 500)  // 淡入（500ms）
        .addPropertyAnim("geometry",
                         QRect(100, 100, 200, 200),       // 初始位置和大小
                         QRect(100, 100, 400, 300),       // 最终位置和大小
                         800)                             // 缩放（800ms）
        .buildSequential(); // 先淡入，再缩放

    anim.start(); // 启动动画
}

#endif // ANIMATIONSEQUENCE_H
