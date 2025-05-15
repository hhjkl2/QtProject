#include "gamesizeedit.h"
#include "ui_gamesizeedit.h"

GameSizeEdit::GameSizeEdit(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameSizeEdit)
{
    // ui->setupUi(this);
    main_layout = new QVBoxLayout;
    mainh_layout = new QHBoxLayout(this);
    width_edit_layout = new QHBoxLayout;
    height_edit_layout = new QHBoxLayout;
    mine_edit_layout = new QHBoxLayout;
    btn_layout = new QHBoxLayout;

    width_edit_label = new QLabel("请选择宽度：",this);
    height_edit_label = new QLabel("请选择高度：",this);
    mine_edit_label = new QLabel("请选择雷数：",this);

    width_edit = new QLineEdit(this);
    height_edit = new QLineEdit(this);
    mine_edit = new QLineEdit(this);
    width_edit->setPlaceholderText("请输入整数");
    height_edit->setPlaceholderText("请输入整数");
    mine_edit->setPlaceholderText("请输入整数");

    confirm_btn = new OwnBtn("确定",this);
    cancel_btn = new OwnBtn("取消",this);

    mainh_layout->addStretch(1);
    mainh_layout->addLayout(main_layout,1);
    mainh_layout->addStretch(1);
    main_layout->addStretch(12);
    main_layout->addLayout(width_edit_layout,1);
    main_layout->addLayout(height_edit_layout,1);
    main_layout->addLayout(mine_edit_layout,1);
    main_layout->addLayout(btn_layout,2);
    main_layout->addStretch(10);
    width_edit_layout->addWidget(width_edit_label);
    width_edit_layout->addWidget(width_edit);
    height_edit_layout->addWidget(height_edit_label);
    height_edit_layout->addWidget(height_edit);
    mine_edit_layout->addWidget(mine_edit_label);
    mine_edit_layout->addWidget(mine_edit);
    btn_layout->addWidget(cancel_btn);
    btn_layout->addWidget(confirm_btn);

    size_policy = new QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    cancel_btn->setSizePolicy(*size_policy);
    confirm_btn->setSizePolicy(*size_policy);
    width_edit_label->setSizePolicy(*size_policy);
    height_edit_label->setSizePolicy(*size_policy);
    mine_edit_label->setSizePolicy(*size_policy);
    width_edit->setSizePolicy(*size_policy);
    height_edit->setSizePolicy(*size_policy);
    mine_edit->setSizePolicy(*size_policy);

    font = new QFont("楷体");

    load_Resources();
}

GameSizeEdit::~GameSizeEdit()
{
    delete ui;
}
void GameSizeEdit::paintEvent(QPaintEvent *event){
    // main_layout->setContentsMargins(this->parentWidget()->width()*0.35,this->parentWidget()->height()*0.4,this->parentWidget()->width()*0.35,this->parentWidget()->height()*0.35);
    main_layout->setSpacing(this->parentWidget()->width()*0.02);

    painter = new QPainter(this);
    QRect rect(this->parentWidget()->width()*0.3,this->parentWidget()->height()*0.3,this->parentWidget()->width()*0.4,this->parentWidget()->height()*0.4);
    // painter->fillRect(rect,Qt::darkGray);
    painter->drawPixmap(rect,*back_ground);

    font->setPointSize(std::min(this->parentWidget()->width(),this->parentWidget()->height())/40);
    width_edit_label->setFont(*font);
    height_edit_label->setFont(*font);
    mine_edit_label->setFont(*font);
    width_edit->setFont(*font);
    height_edit->setFont(*font);
    mine_edit->setFont(*font);
};
void GameSizeEdit::load_Resources(){
    QString temp_image_path = QString(":/main/Resources/Images/%1/over.png").arg(SKINS[SKINS_CASE]);
    back_ground = new QPixmap(temp_image_path);
}
