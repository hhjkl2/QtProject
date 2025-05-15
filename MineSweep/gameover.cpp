#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(QWidget *parent,int pass_time,bool game_state,int size,int width_amount,int height_amount,int mine_amount)
    : QWidget(parent)
    , ui(new Ui::GameOver)
{
    // ui->setupUi(this);
    this->size = size;
    this->passed_time = pass_time;
    game_type = game_state;
    //设定字体
    font = new QFont;
    font->setFamily("楷体");
    font->setPointSize(size/12);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::darkGray);

    //初始化布局
    main_layout = new QVBoxLayout(this);
    main_layout->setAlignment(Qt::AlignCenter);
    main_layout->setSpacing(size/5);
    statics_layout = new QVBoxLayout;
    statics_layout->setAlignment(Qt::AlignCenter);
    statics_layout->setSpacing(size/20);
    btn_layout = new QHBoxLayout;
    btn_layout->setSpacing(size/10);

    //设置游戏信息
    QString game_statics_string = QString("%1×%2——%3个雷").arg(9).arg(9).arg(10);
    game_statics = new QLabel(game_statics_string);
    game_statics->setAlignment(Qt::AlignCenter);

    //设置数据集合
    QString temp_time = "此次历时:"+QString::number(pass_time)+"秒";
    this->pass_time = new QLabel(temp_time);
    QString temp_game_state;
    if(game_state){temp_game_state = "游戏成功";}
    else{temp_game_state = "游戏失败";}
    this->game_state = new QLabel(temp_game_state);

    //设置按钮
    back = new OwnBtn("返回",this);
    again = new OwnBtn("继续",this);
    QSizePolicy size_policy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    back->setSizePolicy(size_policy);
    again->setSizePolicy(size_policy);

    //应用字体
    game_statics->setFont(*font);
    game_statics->setPalette(palette);
    back->setFont(*font);
    again->setFont(*font);
    font->setPointSize(size/10);
    this->pass_time->setFont(*font);
    this->game_state->setFont(*font);

    //设置关系
    main_layout->addStretch(1);
    main_layout->addWidget(game_statics,1);
    main_layout->addLayout(statics_layout,4);
    statics_layout->addStretch(1);
    statics_layout->addWidget(this->game_state,1);
    statics_layout->addWidget(this->pass_time,1);
    //特殊情况加入最高记录
    if(game_state && width_amount == 9 && height_amount == 9 && mine_amount == 10 && MIN_GOOD!=999999){
        MIN_GOOD = std::min(MIN_GOOD,pass_time);
        QString temp_time2 = "最高记录:"+QString::number(MIN_GOOD)+"秒";
        best_time = new QLabel(temp_time2);
        statics_layout->addWidget(best_time,1);
    }else if(game_state && width_amount == 16 && height_amount == 16 && mine_amount == 40 && MID_GOOD!=999999){
        MID_GOOD = std::min(MID_GOOD,pass_time);
        QString temp_time2 = "最高记录:"+QString::number(MID_GOOD)+"秒";
        best_time = new QLabel(temp_time2);
        statics_layout->addWidget(best_time,1);
    }else if(game_state && width_amount == 30 && height_amount == 16 && mine_amount == 99 && MAX_GOOD!=999999){
        MAX_GOOD = std::min(MAX_GOOD,pass_time);
        QString temp_time2 = "最高记录:"+QString::number(MAX_GOOD)+"秒";
        best_time = new QLabel(temp_time2);
        statics_layout->addWidget(best_time,1);
    }
    if(best_time){
        best_time->setFont(*font);
    }
    statics_layout->addStretch(1);
    main_layout->addLayout(btn_layout,1);
    main_layout->addStretch(1);
    btn_layout->addStretch(1);
    btn_layout->addWidget(back,5);
    btn_layout->addWidget(again,5);
    btn_layout->addStretch(1);

    //增加边框
    // frame = new QFrame(this);
    // frame->setFrameStyle(QFrame::Box | QFrame::Sunken);
    // frame->setStyleSheet("QFrame { border: 5px solid black; }");
    // frame->setLineWidth(2);
    // frame->lower();
    // frame->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    //设置窗口大小
    // frame->setFixedSize(size,size*1.5);
    this->setFixedSize(size,size*1.5);

    // connect(back,&QPushButton::clicked,[this](){
    //     qDebug() << "ss";
    // });

    load_Resources();

    //设置颜色
    game_statics->setStyleSheet(QString(COLORS[SKINS_CASE]));
    this->pass_time->setStyleSheet(QString(COLORS[SKINS_CASE]));
    if(best_time)
        this->best_time->setStyleSheet(QString(COLORS[SKINS_CASE]));
    this->game_state->setStyleSheet(QString(COLORS[SKINS_CASE]));
}

GameOver::~GameOver()
{
    delete ui;
}
void GameOver::paintEvent(QPaintEvent *event){
    if(this->parentWidget()){
        this->size = std::min(this->parentWidget()->width(),this->parentWidget()->height())/2;

        font->setPointSize(size/12);

        main_layout->setSpacing(size/5);
        statics_layout->setSpacing(size/20);
        btn_layout->setSpacing(size/10);

        //应用字体
        game_statics->setFont(*font);
        font->setPointSize(size/10);
        this->pass_time->setFont(*font);
        if(best_time){
            best_time->setFont(*font);
        }
        this->game_state->setFont(*font);

        // frame->setFixedSize(size,size*1.5);
        this->setFixedSize(size,size*1.5);

        //移动结算页面位置
        // this->move(this->parentWidget()->width()/2-size/2,this->parentWidget()->height()/2-size*1.5/2);
    }

    painter = new QPainter(this);
    // QString back_ground_path = QString(":/main/Resources/Images/%1/background.png").arg(SKINS[SKINS_CASE]);
    // back_ground = new QPixmap(back_ground_path);
    painter->drawPixmap(0,0,size,size*1.5,*back_ground);

    // painter->fillRect(statics_layout->contentsRect(),Qt::darkGray);

    QWidget::paintEvent(event);
}
void GameOver::load_Resources(){
    QString temp_image_path = QString(":/main/Resources/Images/%1/over.png").arg(SKINS[SKINS_CASE]);
    back_ground = new QPixmap(temp_image_path);
}
