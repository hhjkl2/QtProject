#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChartView>
#include <QLineSeries>
#include <QTimer>
#include <random>  // 添加标准库随机头文件
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateData(); // 定时更新数据槽函数

private:
    QChart *chart;
    QChartView *chartView;
    QLineSeries *series;
    QTimer dataTimer;
    bool isFirstPass = true;     // 首次填充阶段标志
    int writeIndex = 0;          // 当前写入位置
    QVector<QPointF> dataBuffer; // 数据存储区
    std::uniform_real_distribution<double> distribution;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
