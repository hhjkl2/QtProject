#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QSizePolicy>
#include <QFont>
#include <QPixmap>
#include <QPainter>
#include <QString>

#include "overall.h"
#include "ownbtn.h"

namespace Ui {
class StartPage;
}

class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = nullptr);
    ~StartPage();

    QVBoxLayout * mainv_layout;
    QHBoxLayout * mainh_layout;
    OwnBtn * start_game;
    OwnBtn * change_skins;
    OwnBtn * exit_game;
    QSizePolicy * button_policy;

    QString * image_path;
    QPixmap * back_ground;
    QPainter * painter;

    void load_Resources();
    //主窗口大小变化后改变布局，使用内置函数重写，自动调用
    void resizeEvent(QResizeEvent *event) override;

    void paintEvent(QPaintEvent * event) override;
private:
    Ui::StartPage *ui;
};

#endif // STARTPAGE_H
