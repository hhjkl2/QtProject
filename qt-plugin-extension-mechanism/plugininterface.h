#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QObject>

// 定义插件接口类
class PluginInterface {
public:
    virtual ~PluginInterface() {}
    // 纯虚函数，获取插件名称
    virtual QString getName() const = 0;
    // 纯虚函数，执行插件功能
    virtual void performAction() = 0;
};

// 声明接口的唯一标识符
#define PluginInterface_iid "com.example.PluginInterface"

// 向 Qt 元对象系统声明该接口
Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)

#endif // PLUGININTERFACE_H
