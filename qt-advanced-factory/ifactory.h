// ifactory.h 修改后
#ifndef IFACTORY_H
#define IFACTORY_H

#include "iproduct.h"
#include <QObject>
#include <QHash>
#include <QMetaObject>

// 非模板的抽象工厂基类
class IFactory : public QObject {
    Q_OBJECT
public:
    explicit IFactory(QObject* parent = nullptr) : QObject(parent) {} // 新增构造函数
    virtual ~IFactory() = default;
    virtual IProduct* create(QWidget* parent = nullptr) = 0;
};

// 元工厂类（管理工厂的注册与创建）
class MetaFactory : public QObject {
    Q_OBJECT
private:
    QHash<QString, const QMetaObject*> m_factoryMetaObjects;
    static MetaFactory* s_instance;

    explicit MetaFactory(QObject* parent = nullptr) : QObject(parent) {}

public:
    static MetaFactory* instance() {
        static MetaFactory instance;
        return &instance;
    }

    void registerFactory(const QString& typeName, const QMetaObject* meta) {
        m_factoryMetaObjects.insert(typeName, meta);
    }

    template <typename T>
    T* createFactory(const QString& typeName) {
        if (!m_factoryMetaObjects.contains(typeName)) return nullptr;
        const QMetaObject* meta = m_factoryMetaObjects.value(typeName);
        QObject* obj = meta->newInstance(Q_ARG(QObject*, this));
        return qobject_cast<T*>(obj);
    }
};

#endif // IFACTORY_H
