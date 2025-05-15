#include "pluginimpl.h"
#include <QDebug>

// 实现获取插件名称的函数
QString PluginImpl::getName() const {
    return "SamplePlugin";
}

// 实现执行插件功能的函数
void PluginImpl::performAction() {
    qDebug() << "SamplePlugin is performing an action.";
}
