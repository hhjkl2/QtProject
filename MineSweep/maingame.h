#ifndef MAINGAME_H
#define MAINGAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QVector>
#include <QMouseEvent>
#include <QTimer>

#include <random>

#include "overall.h"
#include "sweeparea.h"
#include "gameover.h"

namespace Ui {
class MainGame;
}

class MainGame : public QWidget
{
    Q_OBJECT

public:
    explicit MainGame(QWidget *parent = nullptr,int width_amount = 0,int height_amount = 0,int mine_amount = 0);
    ~MainGame();

    //布局
    QVBoxLayout * main_layout;
    QHBoxLayout * top_layout;
    QHBoxLayout * left_layout;
    QHBoxLayout * right_layout;
    QHBoxLayout * sweep_area_layout;
    QVBoxLayout * cover_over_layout;

    //资源文件
    QPixmap * back_ground;
    //资源路径
    QString * image_path;

    //绘图工具
    QPainter * painter;

    QFont * font;

    //地图
    int **map;
    //雷的总数量
    int mine_number;
    //插旗的数量
    int flag_number = 0;
    //地图长宽的格子数
    int width_amount;
    int height_amount;

    //设置一个计时器
    QTimer * timer;
    //时间统计
    int time_count = 0;
    //时间变化的修改函数
    void time_Pass();

    //判断游戏状态
    bool winGame = false;
    bool gameRunning = true;

    //显示雷数时间等
    QLabel *rest_mine_img;
    QLabel *rest_mine_amount;
    QLabel *pass_time_img;
    QLabel *pass_time_amount;

    //主要雷区
    SweepArea * sweep_area;
    //游戏结束界面
    GameOver * game_over = nullptr;
    QWidget * cover_over = nullptr;

    //点击声音
    QSoundEffect * left_click;
    QSoundEffect * right_click;
    QSoundEffect * boom;
    QSoundEffect * success;

    void load_Resources();
    //地图初始化
    void init_Map(int width_count,int height_count,int mine_amount);
    //重绘背景和状态栏
    void paintEvent(QPaintEvent *event) override;
    //打开空白格子
    void Open_Blanks(int m_height,int m_width);
    //游戏结束操作
    void game_Over();
signals:
    void overCreated();
public slots:
    //点击后修改雷区数据
    void modify_Mine_Area(QMouseEvent *event);
private:
    Ui::MainGame *ui;
};

#endif // MAINGAME_H
