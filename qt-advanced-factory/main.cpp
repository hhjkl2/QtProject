#include <QApplication>
#include <QVBoxLayout>
#include "ifactory.h"
#include "chart_plugin.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 初始化元工厂（注册图表工厂）
    MetaFactory* metaFactory = MetaFactory::instance();
    metaFactory->registerFactory("ChartFactory", &ChartFactory::staticMetaObject);

    // 动态创建工厂实例（从元工厂获取）
    IFactory* chartFactory = metaFactory->createFactory<IFactory>("ChartFactory");
    if (!chartFactory) {
        qCritical() << "Failed to create ChartFactory";
        return -1;
    }

    // 使用工厂创建产品（图表插件）
    IProduct* chartProduct = chartFactory->create();
    if (!chartProduct) {
        qCritical() << "Failed to create ChartProduct";
        return -1;
    }

    // 显示产品 UI
    QWidget mainWindow;
    mainWindow.setWindowTitle("Qt 高级工厂模式示例");
    QVBoxLayout* layout = new QVBoxLayout(&mainWindow);
    layout->addWidget(chartProduct->widget(&mainWindow));  // 获取插件控件

    mainWindow.resize(800, 600);
    mainWindow.show();

    // 执行插件功能
    chartProduct->execute();  // 输出：ChartPlugin: 执行数据更新

    return app.exec();
}
