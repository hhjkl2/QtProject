#ifndef IPRODUCT_H
#define IPRODUCT_H

#include <QObject>
#include <QWidget>

// 抽象产品接口（所有插件需实现此接口）
class IProduct : public QObject {
    Q_OBJECT
public:
    explicit IProduct(QObject* parent = nullptr) : QObject(parent) {} // 新增构造函数
    virtual ~IProduct() = default;
    virtual QString name() const = 0;          // 产品名称
    virtual QWidget* widget(QWidget* parent) = 0;  // 返回 UI 控件（Qt 核心特性）
    virtual void execute() = 0;               // 执行功能
};

// Qt 接口声明（用于动态类型检查）
Q_DECLARE_INTERFACE(IProduct, "com.qt.example.IProduct/1.0")

#endif // IPRODUCT_H
