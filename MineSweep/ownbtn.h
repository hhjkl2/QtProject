#ifndef OWNBTN_H
#define OWNBTN_H

#include <QPushButton>
#include <QString>
#include <QPainter>
#include <QFont>
#include <QFontDatabase>
#include <QSoundEffect>
#include <QUrl>

#include "overall.h"

class OwnBtn : public QPushButton
{
    Q_OBJECT  // 添加 Q_OBJECT 宏
public:
    explicit OwnBtn(const QString &btn_text = "", QWidget *parent = nullptr);

    void enterEvent(QEnterEvent *event) override;

    void leaveEvent(QEvent *event) override;

    void load_Resouces();
    QString nomal_img;
    QString push_img;
    QPainter * painter;
    QString text;
    QFont * font;
    QSoundEffect * pushed;
    bool push = false;
    void paintEvent(QPaintEvent *event) override;
};

#endif // OWNBTN_H
