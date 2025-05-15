#ifndef GAMECHOOSEPAGE_H
#define GAMECHOOSEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QFont>

#include "ownbtn.h"
#include "overall.h"

namespace Ui {
class GameChoosePage;
}

class GameChoosePage : public QWidget
{
    Q_OBJECT

public:
    explicit GameChoosePage(QWidget *parent = nullptr);
    ~GameChoosePage();

    QVBoxLayout * mainv_layout;
    QHBoxLayout * mainh_layout;
    OwnBtn * min_map;
    OwnBtn * mid_map;
    OwnBtn * max_map;
    OwnBtn * free_map;
    OwnBtn * back_btn;
    QSizePolicy * button_policy;

    QString * image_path;
    QPixmap * back_ground;
    QPainter * painter;

    void load_Resources();
    //主窗口大小变化后改变布局，使用内置函数重写，自动调用
    void resizeEvent(QResizeEvent *event) override;

    void paintEvent(QPaintEvent * event) override;
private:
    Ui::GameChoosePage *ui;
};

#endif // GAMECHOOSEPAGE_H
