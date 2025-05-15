#include <QCoreApplication>
#include <QPluginLoader>
#include <QDebug>
#include "plugininterface.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // 创建插件加载器，指定插件路径
    QPluginLoader loader("libSamplePlugin.dll");
    // 尝试加载插件
    QObject *pluginObject = loader.instance();

    if (pluginObject) {
        // 检查插件对象是否实现了指定接口
        PluginInterface *plugin = qobject_cast<PluginInterface*>(pluginObject);
        if (plugin) {
            // 输出插件名称
            qDebug() << "Plugin name:" << plugin->getName();
            // 调用插件功能
            plugin->performAction();
        } else {
            qDebug() << "Plugin does not implement the required interface.";
        }
    } else {
        qDebug() << "Failed to load plugin:" << loader.errorString();
    }

    return a.exec();
}
