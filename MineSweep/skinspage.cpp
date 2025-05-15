#include "skinspage.h"
#include "ui_skinspage.h"

SkinsPage::SkinsPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SkinsPage)
{
    // ui->setupUi(this);

    //初始化布局和完成界面
    mainv_layout = new QVBoxLayout(this);
    mainv_layout->setAlignment(Qt::AlignHCenter);
    pictures_layout = new QGridLayout(this);
    last = new OwnBtn("上一个",this);
    finish = new OwnBtn("完成",this);
    next = new OwnBtn("下一个",this);
    button_layout = new QHBoxLayout(this);
    pictures_hlayout = new QHBoxLayout();
    button_layout->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    button_layout->addStretch(2);
    button_layout->addWidget(last,2);
    button_layout->addWidget(finish,2);
    button_layout->addWidget(next,2);
    button_layout->addStretch(2);
    mainv_layout->addStretch(2);
    mainv_layout->addLayout(pictures_hlayout,6);
    mainv_layout->addLayout(button_layout,1);
    mainv_layout->addStretch(1);

    pictures_hlayout->addStretch(2);
    pictures_hlayout->addLayout(pictures_layout,6);
    pictures_hlayout->addStretch(2);

    QSizePolicy button_policy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    last->setSizePolicy(button_policy);
    finish->setSizePolicy(button_policy);
    next->setSizePolicy(button_policy);

    load_Resources();
}

SkinsPage::~SkinsPage()
{
    delete ui;
}
void SkinsPage::resizeEvent(QResizeEvent *event){
    // mainv_layout->setContentsMargins(this->parentWidget()->width()*0.1,this->parentWidget()->height()*0.3,this->parentWidget()->width()*0.1,this->parentWidget()->height()*0.1);
    mainv_layout->setSpacing(this->parentWidget()->width()*0.05);
    // finish->setFixedSize(this->parentWidget()->width()*0.2,this->parentWidget()->height()*0.08);

    QWidget::resizeEvent(event);
}
void SkinsPage::load_Resources(){
    QString temp_image_path = QString(":/main/Resources/Images/%1/startpage.png").arg(SKINS[SKINS_CASE]);
    back_ground = new QPixmap(temp_image_path);

    for (int i = 0; i <= 11; ++i) {
        QString img_path = QString(":/main/Resources/Images/%1/%2.jpg").arg(SKINS[SKINS_CASE]).arg(i);
        QPixmap * init_img = new QPixmap(img_path);
        temp = new QLabel(this);
        temp->setPixmap((*init_img).scaled(size()/20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        pictures_layout->addWidget(temp,i/4,i%4);
        pictures_label.emplace_back(temp);
        pictures_pixmap.emplace_back(init_img);
    }

    QString img_path = QString(":/main/Resources/Images/%1/btn.png").arg(SKINS[SKINS_CASE]);
    QPixmap * temp_img = new QPixmap(img_path);
    temp = new QLabel(this);
    pictures_label.emplace_back(temp);
    pictures_pixmap.emplace_back(temp_img);
    temp->setPixmap((*temp_img).scaled(size()/5, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    pictures_layout->addWidget(temp,3,0);
    img_path = QString(":/main/Resources/Images/%1/btn_push.png").arg(SKINS[SKINS_CASE]);
    temp_img = new QPixmap(img_path);
    temp = new QLabel(this);
    pictures_label.emplace_back(temp);
    pictures_pixmap.emplace_back(temp_img);
    temp->setPixmap((*temp_img).scaled(size()/5, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    pictures_layout->addWidget(temp,4,0);

    img_path = QString(":/main/Resources/Images/%1/over.png").arg(SKINS[SKINS_CASE]);
    temp_img = new QPixmap(img_path);
    temp = new QLabel(this);
    pictures_label.emplace_back(temp);
    pictures_pixmap.emplace_back(temp_img);
    temp->setPixmap((*temp_img).scaled(size()/5, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    pictures_layout->addWidget(temp,3,2);

    last->load_Resouces();
    finish->load_Resouces();
    next->load_Resouces();
}
void SkinsPage::paintEvent(QPaintEvent *event){
    painter = new QPainter(this);
    painter->drawPixmap(0,0,width(),height(),*back_ground);

    pictures_layout->setSpacing(this->x()/100);

    for (int i = 0; i <= 11; ++i) {
        pictures_label[i]->setPixmap(pictures_pixmap[i]->scaled(size()/20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    pictures_label[12]->setPixmap(pictures_pixmap[12]->scaled(size()/5, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    pictures_label[13]->setPixmap(pictures_pixmap[13]->scaled(size()/5, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    pictures_label[14]->setPixmap(pictures_pixmap[14]->scaled(size()/5, Qt::KeepAspectRatio, Qt::SmoothTransformation));
};
