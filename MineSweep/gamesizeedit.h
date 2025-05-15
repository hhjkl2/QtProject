#ifndef GAMESIZEEDIT_H
#define GAMESIZEEDIT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSizePolicy>
#include <QPainter>
#include <QFont>

#include "ownbtn.h"

namespace Ui {
class GameSizeEdit;
}

class GameSizeEdit : public QWidget
{
    Q_OBJECT

public:
    explicit GameSizeEdit(QWidget *parent = nullptr);
    ~GameSizeEdit();

    QVBoxLayout * main_layout;
    QHBoxLayout * mainh_layout;
    QHBoxLayout * width_edit_layout;
    QHBoxLayout * height_edit_layout;
    QHBoxLayout * mine_edit_layout;
    QHBoxLayout * btn_layout;

    QLabel * width_edit_label;
    QLabel * height_edit_label;
    QLabel * mine_edit_label;

    QLineEdit * width_edit;
    QLineEdit * height_edit;
    QLineEdit * mine_edit;

    OwnBtn * confirm_btn;
    OwnBtn * cancel_btn;

    QSizePolicy * size_policy;

    QPainter * painter;

    QPixmap * back_ground;

    QFont * font;

    void load_Resources();
    void paintEvent(QPaintEvent *event) override;
private:
    Ui::GameSizeEdit *ui;
};

#endif // GAMESIZEEDIT_H
