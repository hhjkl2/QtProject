#include <QApplication>
#include "animationsequence.h"
#include "tablecomponent.h"
#include "threadtask.h"
#include <QMainWindow>
#include <QTimer>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 创建主窗口并设置基本属性
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Qt Builder 示例");
    mainWindow.resize(600, 400);

    // 设置中心部件用于布局
    QWidget *centralWidget = new QWidget(&mainWindow);
    mainWindow.setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 添加一个子部件作为动画目标（可选）
    QWidget *animationTarget = new QWidget(centralWidget);
    animationTarget->setFixedSize(100, 100);
    animationTarget->setStyleSheet("background-color: blue;");
    mainLayout->addWidget(animationTarget);

    // 显示主窗口后，通过单次定时器触发动画（确保窗口已显示）
    QTimer::singleShot(100, [&]() {
        // 示例1: 播放窗口动画（主窗口淡入+缩放）
        createWindowAnimation(&mainWindow);

        // 示例2: 创建并显示财务表格
        createFinanceTable(centralWidget); // 表格会添加到中心部件的布局中
    });

    // 示例3: 启动后台任务
    createBackgroundTask();

    mainWindow.show();
    return app.exec();
}
