#ifndef WIDGET_H
#define WIDGET_H

#include "startpage.h"
#include "skinspage.h"
#include "gamechoosepage.h"
#include "maingame.h"
#include "gamesizeedit.h"

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT//Q_OBJECT宏，允许本类中使用信号和槽的机制

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QStackedWidget * widgets;
    StartPage * start_page;
    GameChoosePage * game_choose_page;
    SkinsPage * skins_page;
    MainGame * main_game;
    GameSizeEdit * game_size_edit;
    QWidget * cover_game_size_edit = nullptr;

    QVBoxLayout * main_layout;
    QVBoxLayout * cover_game_size_edit_layout;

    void playAgain();

    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
