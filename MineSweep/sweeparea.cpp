#include "sweeparea.h"
#include "ui_sweeparea.h"

SweepArea::SweepArea(QWidget *parent,int **map,int width,int height)
    : QWidget(parent)
    , ui(new Ui::SweepArea)
{
    // ui->setupUi(this);
    //地图数据传递
    this->map = map;
    this->width = width;
    this->height = height;
    //加载资源
    img_vec = new QVector<QPixmap *>;
    load_Resources();

    QPainter painter(this);
    for(int i = 0;i<height;i++){
        for (int j = 0; j < width; ++j)
        {
            //加载数字和雷
            if(map[i][j]>=0 && map[i][j] <=8){
                painter.drawPixmap(i*MINE_SIZE,j*MINE_SIZE,MINE_SIZE,MINE_SIZE,*(*img_vec)[map[i][j]]);
            }
            else if(map[i][j] == -1)
            {
                painter.drawPixmap(i*MINE_SIZE,j*MINE_SIZE,MINE_SIZE,MINE_SIZE,*(*img_vec)[9]);
            }else if(map[i][j] >= 19 && map[i][j]<=28){
                painter.drawPixmap(i*MINE_SIZE,j*MINE_SIZE,MINE_SIZE,MINE_SIZE,*(*img_vec)[10]);
            }else if(map[i][j] >= 39){
                painter.drawPixmap(i*MINE_SIZE,j*MINE_SIZE,MINE_SIZE,MINE_SIZE,*(*img_vec)[11]);
            }
        }
    }
}

SweepArea::~SweepArea()
{
    delete ui;
}
void SweepArea::load_Resources(){
    //加载雷区
    for (int i = 0; i <= 11; ++i) {
        QString temp_img_path = QString(":/main/Resources/Images/%1/%2.jpg").arg(SKINS[SKINS_CASE]).arg(i);
        img_path = new QString(temp_img_path);
        init_img = new QPixmap(*img_path);
        img_vec->emplace_back(init_img);
    }
};
//按下鼠标按键后自动调用
void SweepArea::mousePressEvent(QMouseEvent *event){
    emit mouseSignal(event);
    // for (int i = 0; i < this->height; ++i) {
    //     for (int j = 0; j < this->width; ++j) {
    //         qDebug() << map[i][j];
    //     }
    // }
    // qDebug() << height << ' ' << width;
}
//重绘雷区
void SweepArea::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    for(int i = 0;i<height;i++){
        for (int j = 0; j < width; ++j)
        {
            //加载数字和雷
            if(map[i][j]>=0 && map[i][j] <=8){
                painter.drawPixmap(j*MINE_SIZE,i*MINE_SIZE,MINE_SIZE,MINE_SIZE,*(*img_vec)[map[i][j]]);
            }
            else if(map[i][j] == -1)
            {
                painter.drawPixmap(j*MINE_SIZE,i*MINE_SIZE,MINE_SIZE,MINE_SIZE,*(*img_vec)[9]);
            }else if(map[i][j] >= 19 && map[i][j]<=28){
                painter.drawPixmap(j*MINE_SIZE,i*MINE_SIZE,MINE_SIZE,MINE_SIZE,*(*img_vec)[10]);
            }else if(map[i][j] >= 39){
                painter.drawPixmap(j*MINE_SIZE,i*MINE_SIZE,MINE_SIZE,MINE_SIZE,*(*img_vec)[11]);
            }
        }
    }
}
void SweepArea::wheelEvent(QWheelEvent *event){
    if (event->angleDelta().y() > 0)
    {
        // 滚轮向上滚动，增加参数的值
        MINE_SIZE++;
    }
    else
    {
        MINE_SIZE--;
    }
    update();
    event->accept();
}
