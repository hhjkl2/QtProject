#include "startpage.h"
#include "ui_startpage.h"

StartPage::StartPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartPage)
{
    // ui->setupUi(this);
    //初始化按钮
    mainv_layout = new QVBoxLayout;
    mainh_layout = new QHBoxLayout;
    start_game = new OwnBtn("开始游戏");
    change_skins = new OwnBtn("更改外观");
    exit_game = new OwnBtn("退出游戏");
    //初始化布局，并作用于整个控件集合
    this->setLayout(mainh_layout);
    // main_layout->setContentsMargins(parent->width()*0.2,parent->height()*0.2,parent->width()*0.2,parent->height()*0.2);
    mainh_layout->addStretch(3);
    mainh_layout->addLayout(mainv_layout,4);
    mainh_layout->addStretch(3);
    mainv_layout->addStretch(5);
    mainv_layout->setSpacing(parent->width()*0.03);
    //设定按钮为可拉伸
    button_policy = new QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    start_game->setSizePolicy(*button_policy);
    change_skins->setSizePolicy(*button_policy);
    exit_game->setSizePolicy(*button_policy);
    //将按钮添加至布局中
    mainv_layout->addWidget(start_game,1);
    mainv_layout->addWidget(change_skins,1);
    mainv_layout->addWidget(exit_game,1);
    mainv_layout->addStretch(2);

    load_Resources();
}
StartPage::~StartPage()
{
    delete ui;
}
//主窗口大小变化后，改变布局
void StartPage::resizeEvent(QResizeEvent *event){
    // main_layout->setContentsMargins(this->parentWidget()->width()*0.3,this->parentWidget()->height()*0.4,this->parentWidget()->width()*0.3,this->parentWidget()->height()*0.2);
    mainv_layout->setSpacing(this->parentWidget()->width()*0.03);
    QWidget::resizeEvent(event);
}
void StartPage::paintEvent(QPaintEvent * event){
    painter = new QPainter(this);
    painter->drawPixmap(0,0,width(),height(),*back_ground);
}
void StartPage::load_Resources(){
    QString temp_image_path = QString(":/main/Resources/Images/%1/startpage.png").arg(SKINS[SKINS_CASE]);
    image_path = new QString(temp_image_path);
    back_ground = new QPixmap(*image_path);
    start_game->load_Resouces();
    change_skins->load_Resouces();
    exit_game->load_Resouces();
};
