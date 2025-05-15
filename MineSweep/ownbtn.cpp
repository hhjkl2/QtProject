#include "ownbtn.h"

OwnBtn::OwnBtn(const QString &btn_text, QWidget *parent) : QPushButton(parent){
    // 初始显示正常状态的图片
    text = btn_text;
    // setText(btn_text);
    setIcon(QIcon(QPixmap(nomal_img).scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    // setIconSize(QPixmap(nomal_img).size());
    setStyleSheet("QPushButton { border: none; }");
    font = new QFont("楷体");
    pushed = new QSoundEffect(this);
    load_Resouces();
    connect(this, &QPushButton::clicked, [&]() {
        qDebug() << "pushed";
        pushed->play();
    });
}
void OwnBtn::enterEvent(QEnterEvent *event){
    // 鼠标进入按钮区域，切换为悬停状态的图片
    // setIconSize(QPixmap(push_img).size());
    push = true;
    update();
    QPushButton::enterEvent(event);
}
void OwnBtn::leaveEvent(QEvent *event){
    // 鼠标离开按钮区域，切换回正常状态的图片
    // setIconSize(QPixmap(nomal_img).size());
    push = false;
    update();
    QPushButton::leaveEvent(event);
}
void OwnBtn::load_Resouces(){
    nomal_img = QString(":/main/Resources/Images/%1/btn.png").arg(SKINS[SKINS_CASE]);
    push_img = QString(":/main/Resources/Images/%1/btn_push.png").arg(SKINS[SKINS_CASE]);
    QString pushed_media = QString(":/main/Resources/Images/%1/btn_push.wav").arg(SKINS[SKINS_CASE]);
    QUrl pushed_media2 = QUrl::fromLocalFile(pushed_media);
    pushed->setSource(pushed_media2);
    // if(pushed->isLoaded()) qDebug() << "yes";else qDebug() << "no";
    pushed->setVolume(1.0);
}
void OwnBtn::paintEvent(QPaintEvent *event){
    painter = new QPainter(this);
    if(push){
        painter->drawPixmap(0,0,QPixmap(push_img).scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }else{
        painter->drawPixmap(0,0,QPixmap(nomal_img).scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    if(SKINS_CASE==0)
        painter->setPen(Qt::black);
    else
        painter->setPen(Qt::white);
    font->setPointSizeF(12 * qMin(width() / 100.0, height() / 50.0));
    painter->setFont(*font);
    painter->drawText(rect(), Qt::AlignCenter,text);
};
