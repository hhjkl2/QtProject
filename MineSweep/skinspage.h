#ifndef SKINSPAGE_H
#define SKINSPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QString>
#include <QPainter>
#include <QGridLayout>
#include <QVector>

#include "overall.h"
#include "ownbtn.h"

namespace Ui {
class SkinsPage;
}

class SkinsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SkinsPage(QWidget *parent = nullptr);
    ~SkinsPage();

    QVBoxLayout * mainv_layout;
    QHBoxLayout * button_layout;
    QGridLayout * pictures_layout;
    QHBoxLayout * pictures_hlayout;
    OwnBtn * finish;
    OwnBtn * last;
    OwnBtn * next;
    QLabel *temp;

    QPainter * painter;

    QPixmap * back_ground;

    QString * back_path;

    QVector<QLabel *> pictures_label;
    QVector<QPixmap *> pictures_pixmap;

    void load_Resources();
    //主窗口大小变化后改变布局，使用内置函数重写，自动调用
    void resizeEvent(QResizeEvent *event) override;

    void paintEvent(QPaintEvent *event) override;
private:
    Ui::SkinsPage *ui;
};

#endif // SKINSPAGE_H
