#ifndef TEMPLATECLASS_HPP
#define TEMPLATECLASS_HPP

#include <QDebug>
#include <QObject>

// 模板类定义
template <typename T>
class TemplateClass : public QObject
{
    // Q_OBJECT
public:
    // 静态成员变量
    static int instanceCount;

    // 构造函数
    TemplateClass(T value, QObject *parent = nullptr) : QObject(parent), m_value(value)
    {
        instanceCount++;
    }

    // 析构函数
    ~TemplateClass()
    {
        instanceCount--;
    }

    // 成员函数
    void printValue()
    {
        qDebug() << "Value: " << m_value;
    }

private:
    T m_value;
};

// 静态成员变量的初始化
template <typename T>
int TemplateClass<T>::instanceCount = 0;

#endif // TEMPLATECLASS_HPP
