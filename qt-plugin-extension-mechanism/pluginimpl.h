#ifndef PLUGINIMPL_H
#define PLUGINIMPL_H

#include <QObject>
#include "plugininterface.h"

// 插件实现类，继承自 QObject 和插件接口
class PluginImpl : public QObject, public PluginInterface {
    Q_OBJECT
    // 关联插件元数据与接口标识符
    Q_PLUGIN_METADATA(IID PluginInterface_iid)// Failed to load plugin: libSamplePlugin.dll is not a Qt plugin (metadata not found)
    // 声明该类实现了指定接口
    //Q_INTERFACES(PluginInterface)

public:
    // 重写获取插件名称的函数
    QString getName() const override;
    // 重写执行插件功能的函数
    void performAction() override;
};

#endif // PLUGINIMPL_H
