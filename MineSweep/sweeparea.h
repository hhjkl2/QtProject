#ifndef SWEEPAREA_H
#define SWEEPAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPixmap>
#include <QVector>
#include <QPainter>

#include "overall.h"

namespace Ui {
class SweepArea;
}

class SweepArea : public QWidget
{
    Q_OBJECT

public:
    explicit SweepArea(QWidget *parent = nullptr,int **map = nullptr,int width = 0,int height = 0);
    ~SweepArea();

    //资源文件
    QVector<QPixmap *> *img_vec;
    QPixmap * init_img;
    QString * img_path;

    //地图数据
    int **map;
    int width;
    int height;
    //加载资源
    void load_Resources();
    //检测鼠标按下并返回坐标
    void mousePressEvent(QMouseEvent *event) override;
    //鼠标滚轮修改图片大小
    void wheelEvent(QWheelEvent *event) override;
    //重绘雷区
    void paintEvent(QPaintEvent *event) override;
    //点击后发送自定义信号
private:
    Ui::SweepArea *ui;
signals:
    void mouseSignal(QMouseEvent *event);
};

#endif // SWEEPAREA_H
