// main.cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("qmlTest", "Main");
    if (engine.rootObjects().isEmpty()) {
        qDebug() << "Failed to load QML!";
        return -1;
    }

    engine.setOutputWarningsToStandardError(true); // 输出QML警告到控制台
    QLoggingCategory::setFilterRules("qml.debug=true"); // 启用QML调试日志
    return app.exec();
}
