#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "order_model.h"
#include "status_filter_proxy.h"
#include "time_sort_proxy.h"
#include "async_order_proxy.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 1. 创建异步加载代理（模拟远程订单）
    AsyncOrderProxy asyncProxy;
    asyncProxy.loadFromUrl(QUrl("https://api.example.com/orders"));

    // 2. 链式代理：异步加载 → 过滤 → 排序
    StatusFilterProxy filterProxy;
    filterProxy.setSourceModel(&asyncProxy);
    filterProxy.setTargetStatus("已发货"); // 仅显示已发货订单

    TimeSortProxy sortProxy;
    sortProxy.setSourceModel(&filterProxy);
    sortProxy.sort(1, Qt::DescendingOrder); // 按时间降序排序

    qDebug() << "AsyncProxy rows:" << asyncProxy.rowCount();
    qDebug() << "FilterProxy rows:" << filterProxy.rowCount();
    qDebug() << "SortProxy rows:" << sortProxy.rowCount();

    // 3. QML集成：将最终代理模型暴露给QML
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qt-proxy-model-full-example/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("cppProxyModel", &sortProxy);
    engine.load(url);

    return app.exec();
}
