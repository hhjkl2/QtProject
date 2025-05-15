#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFont>

#include "overall.h"
#include "ownbtn.h"

namespace Ui {
class GameOver;
}

class GameOver : public QWidget
{
    Q_OBJECT

public:
    explicit GameOver(QWidget *parent = nullptr,int pass_time = 0,bool game_state = false,int size = 0,int width_amount = 0,int height_amount = 0,int mine_amount = 0);
    ~GameOver();

    QVBoxLayout * main_layout;
    QVBoxLayout * statics_layout;
    QHBoxLayout * btn_layout;
    QLabel * pass_time;
    QLabel * best_time;
    QLabel * game_state;
    QLabel * game_statics;
    QFrame * frame;
    QPixmap * back_ground;
    QPainter * painter;
    QFont *font;

    int size;
    int passed_time;
    bool game_type;

    OwnBtn *again;
    OwnBtn *back;

    void load_Resources();
    void paintEvent(QPaintEvent *event) override;
private:
    Ui::GameOver *ui;
};

#endif // GAMEOVER_H
