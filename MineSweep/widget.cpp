#include "widget.h"
#include "./ui_widget.h"

#include <QLabel>
#include <QString>
#include "overall.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //获取外界数据
    QFile file("config.txt");
    if(!file.exists()){
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            file.close();
        }
    }
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        QString a,b,c,d,e;
        in >> a;
        in >> b;
        if(!a.isEmpty()){
            QStringList size = a.split(':');
            MINE_SIZE = size[1].toInt();
        }
        if(!b.isEmpty()){
            QStringList skin = b.split(':');
            SKINS_CASE = skin[1].toInt();
        }
        if(!c.isEmpty()){
            QStringList old = c.split(':');
            MIN_GOOD = old[1].toInt();
        }
        if(!c.isEmpty()){
            QStringList old = c.split(':');
            MID_GOOD = old[1].toInt();
        }
        if(!c.isEmpty()){
            QStringList old = c.split(':');
            MAX_GOOD = old[1].toInt();
        }
        file.close();
    }
    //初始化QStackedWidget并加入布局管理
    main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(main_layout);
    widgets = new QStackedWidget();
    main_layout->addWidget(widgets);
    //初始化开始菜单页
    start_page = new StartPage(this);
    widgets->addWidget(start_page);
    //初始化地图选择页
    game_choose_page = new GameChoosePage(this);
    widgets->addWidget(game_choose_page);
    //初始化皮肤更换页
    skins_page = new SkinsPage(this);
    widgets->addWidget(skins_page);
    //与地图选择界面之间的切换
    connect(start_page->start_game,&QPushButton::clicked,[this](){
        widgets->setCurrentIndex(1);
    });
    connect(game_choose_page->back_btn,&QPushButton::clicked,[this](){
        widgets->setCurrentIndex(0);
    });
    //与皮肤界面之间的切换
    connect(start_page->change_skins,&QPushButton::clicked,[this](){
        widgets->setCurrentIndex(2);
    });
    connect(skins_page->finish,&QPushButton::clicked,[this](){
        widgets->setCurrentIndex(0);
    });
    //皮肤界面的皮肤切换
    connect(skins_page->last,&QPushButton::clicked,[this](){
        SKINS_CASE = (SKINS_CASE+2-1)%2;
        start_page->load_Resources();
        skins_page->load_Resources();
        game_choose_page->load_Resources();
        update();
    });
    connect(skins_page->next,&QPushButton::clicked,[this](){
        SKINS_CASE = (SKINS_CASE+2+1)%2;
        start_page->load_Resources();
        skins_page->load_Resources();
        game_choose_page->load_Resources();
        update();
    });
    //对游戏的退出
    connect(start_page->exit_game,&QPushButton::clicked,qApp,&QApplication::quit);
    //进入正式游戏
    connect(game_choose_page->min_map,&QPushButton::clicked,[this](){
        main_game = new MainGame(this,9,9,10);
        widgets->addWidget(main_game);
        widgets->setCurrentIndex(3);
        connect(main_game,&MainGame::overCreated,[this](){
            connect(main_game->game_over->back,&QPushButton::clicked,[this](){
                if(main_game->winGame)
                    MIN_GOOD = std::min(MIN_GOOD,main_game->game_over->passed_time);
                main_game->deleteLater();
                widgets->setCurrentIndex(0);
            });
            connect(main_game->game_over->again,&QPushButton::clicked,[this](){
                if(main_game->winGame)
                    MIN_GOOD = std::min(MIN_GOOD,main_game->game_over->passed_time);
                playAgain();
            });
        });
    });
    connect(game_choose_page->mid_map,&QPushButton::clicked,[this](){
        main_game = new MainGame(this,16,16,40);
        widgets->addWidget(main_game);
        widgets->setCurrentIndex(3);
        connect(main_game,&MainGame::overCreated,[this](){
            connect(main_game->game_over->back,&QPushButton::clicked,[this](){
                if(main_game->winGame)
                    MID_GOOD = std::min(MID_GOOD,main_game->game_over->passed_time);
                main_game->deleteLater();
                widgets->setCurrentIndex(0);
            });
            connect(main_game->game_over->again,&QPushButton::clicked,[this](){
                if(main_game->winGame)
                    MID_GOOD = std::min(MID_GOOD,main_game->game_over->passed_time);
                playAgain();
            });
        });
    });
    connect(game_choose_page->max_map,&QPushButton::clicked,[this](){
        main_game = new MainGame(this,30,16,99);
        widgets->addWidget(main_game);
        widgets->setCurrentIndex(3);
        connect(main_game,&MainGame::overCreated,[this](){
            connect(main_game->game_over->back,&QPushButton::clicked,[this](){
                if(main_game->winGame)
                    MAX_GOOD = std::min(MAX_GOOD,main_game->game_over->passed_time);
                main_game->deleteLater();
                widgets->setCurrentIndex(0);
            });
            connect(main_game->game_over->again,&QPushButton::clicked,[this](){
                if(main_game->winGame)
                    MAX_GOOD = std::min(MAX_GOOD,main_game->game_over->passed_time);
                playAgain();
            });
        });
    });
    connect(game_choose_page->free_map,&QPushButton::clicked,[this]{
        game_size_edit = new GameSizeEdit(this);
        cover_game_size_edit = new QWidget(this);
        cover_game_size_edit->setFixedSize(width(),height());
        cover_game_size_edit_layout = new QVBoxLayout(cover_game_size_edit);
        cover_game_size_edit_layout->setAlignment(Qt::AlignCenter);
        cover_game_size_edit_layout->addWidget(game_size_edit);
        cover_game_size_edit->show();
        game_size_edit->show();
        connect(game_size_edit->cancel_btn,&QPushButton::clicked,[this]{
            OwnBtn* cancelOwnBtn = qobject_cast<OwnBtn*>(game_size_edit->cancel_btn);
            if (cancelOwnBtn) {
                // 监听播放结束信号
                QObject::connect(cancelOwnBtn->pushed, &QSoundEffect::playingChanged, [this, cancelOwnBtn]() {
                    if (!cancelOwnBtn->pushed->isPlaying()) {
                        cover_game_size_edit->deleteLater(); // 音频结束后再销毁
                        cover_game_size_edit = nullptr;
                    }
                });
            }else{
                cover_game_size_edit->deleteLater();
                cover_game_size_edit = nullptr;
            }
        });
        connect(game_size_edit->confirm_btn,&QPushButton::clicked,[this]{
            QString temp_width(game_size_edit->width_edit->text());
            QString temp_height(game_size_edit->height_edit->text());
            QString temp_mine(game_size_edit->mine_edit->text());
            cover_game_size_edit->deleteLater();
            cover_game_size_edit = nullptr;
            main_game = new MainGame(this,std::max(temp_width.toInt(),1),std::max(temp_height.toInt(),1),std::max(temp_mine.toInt(),1));
            widgets->addWidget(main_game);
            widgets->setCurrentIndex(3);
            connect(main_game,&MainGame::overCreated,[this](){
                connect(main_game->game_over->back,&QPushButton::clicked,[this](){
                    main_game->deleteLater();
                    widgets->setCurrentIndex(0);
                });
                connect(main_game->game_over->again,&QPushButton::clicked,[this](){
                    playAgain();
                });
            });
        });
    });
}
Widget::~Widget()
{
    delete ui;
    QFile file("config.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "MINE_SIZE:" << MINE_SIZE << '\n';
    out << "SKINS_CASE:" << SKINS_CASE << '\n';
    out << "MIN:" << MIN_GOOD << '\n';
    out << "MID:" << MID_GOOD << '\n';
    out << "MAX:" << MAX_GOOD;
    file.close();
}
void Widget::resizeEvent(QResizeEvent *event){
    if(cover_game_size_edit) cover_game_size_edit->setFixedSize(width(),height());
};
void Widget::playAgain(){
    int width = main_game->width_amount;
    int height = main_game->height_amount;
    int mine = main_game->mine_number;
    main_game->deleteLater();
    main_game = new MainGame(this,width,height,mine);
    widgets->addWidget(main_game);
    widgets->setCurrentIndex(3);
    connect(main_game,&MainGame::overCreated,[this](){
        connect(main_game->game_over->back,&QPushButton::clicked,[this](){
            if(main_game->winGame && main_game->width_amount == 9 && main_game->height_amount == 9 && main_game->mine_number == 10){
                MIN_GOOD = std::min(MIN_GOOD,main_game->game_over->passed_time);
            }else if(main_game->winGame && main_game->width_amount == 16 && main_game->height_amount == 16 && main_game->mine_number == 40){
                MID_GOOD = std::min(MID_GOOD,main_game->game_over->passed_time);
            }else if(main_game->winGame && main_game->width_amount == 30 && main_game->height_amount == 16 && main_game->mine_number == 99){
                MAX_GOOD = std::min(MAX_GOOD,main_game->game_over->passed_time);
            }
            main_game->deleteLater();
            widgets->setCurrentIndex(0);
        });
        connect(main_game->game_over->again,&QPushButton::clicked,[this](){
            if(main_game->winGame && main_game->width_amount == 9 && main_game->height_amount == 9 && main_game->mine_number == 10){
                MIN_GOOD = std::min(MIN_GOOD,main_game->game_over->passed_time);
            }else if(main_game->winGame && main_game->width_amount == 16 && main_game->height_amount == 16 && main_game->mine_number == 40){
                MID_GOOD = std::min(MID_GOOD,main_game->game_over->passed_time);
            }else if(main_game->winGame && main_game->width_amount == 30 && main_game->height_amount == 16 && main_game->mine_number == 99){
                MAX_GOOD = std::min(MAX_GOOD,main_game->game_over->passed_time);
            }
            playAgain();
        });
    });
};
