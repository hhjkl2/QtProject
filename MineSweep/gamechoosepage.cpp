#include "gamechoosepage.h"
#include "ui_gamechoosepage.h"

GameChoosePage::GameChoosePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameChoosePage)
{
    // ui->setupUi(this);
    //初始化按钮
    mainh_layout = new QHBoxLayout;
    mainv_layout = new QVBoxLayout;
    min_map = new OwnBtn("小型地图");
    mid_map = new OwnBtn("中型地图");
    max_map = new OwnBtn("大型地图");
    free_map = new OwnBtn("自由地图");
    back_btn = new OwnBtn("返回");
    //初始化布局，并作用于整个控件集合
    mainh_layout->addStretch(3);
    mainh_layout->addLayout(mainv_layout,5);
    mainh_layout->addStretch(3);
    this->setLayout(mainh_layout);
    mainv_layout->addStretch(4);
    // main_layout->setContentsMargins(parent->width()*0.2,parent->height()*0.2,parent->width()*0.2,parent->height()*0.2);
    mainv_layout->setSpacing(parent->width()*0.01);
    //设定按钮为可拉伸
    button_policy = new QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    min_map->setSizePolicy(*button_policy);
    mid_map->setSizePolicy(*button_policy);
    max_map->setSizePolicy(*button_policy);
    free_map->setSizePolicy(*button_policy);
    back_btn->setSizePolicy(*button_policy);
    //将按钮添加至布局中
    mainv_layout->addWidget(min_map,1);
    mainv_layout->addWidget(mid_map,1);
    mainv_layout->addWidget(max_map,1);
    mainv_layout->addWidget(free_map,1);
    mainv_layout->addWidget(back_btn,1);
    mainv_layout->addStretch(2);

    load_Resources();
}
GameChoosePage::~GameChoosePage()
{
    delete ui;
}
//主窗口大小变化后，改变布局
void GameChoosePage::resizeEvent(QResizeEvent *event){
    // main_layout->setContentsMargins(this->parentWidget()->width()*0.3,this->parentWidget()->height()*0.4,this->parentWidget()->width()*0.3,this->parentWidget()->height()*0.2);
    mainv_layout->setSpacing(this->parentWidget()->width()*0.01);
    QWidget::resizeEvent(event);
}
void GameChoosePage::paintEvent(QPaintEvent *event){
    painter = new QPainter(this);
    painter->drawPixmap(0,0,width(),height(),*back_ground);
}
void GameChoosePage::load_Resources(){
    QString temp_image_path = QString(":/main/Resources/Images/%1/startpage.png").arg(SKINS[SKINS_CASE]);
    image_path = new QString(temp_image_path);
    back_ground = new QPixmap(*image_path);
    min_map->load_Resouces();
    mid_map->load_Resouces();
    max_map->load_Resouces();
    free_map->load_Resouces();
    back_btn->load_Resouces();
};
