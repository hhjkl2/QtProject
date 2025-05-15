#include "maingame.h"
#include "ui_maingame.h"

MainGame::MainGame(QWidget *parent,int width_amount,int height_amount,int mine_amount)
    : QWidget(parent)
    , ui(new Ui::MainGame)
{
    // ui->setupUi(this);
    //初始化布局
    main_layout = new QVBoxLayout(this);
    // main_layout->setAlignment(Qt::AlignTop);
    top_layout = new QHBoxLayout;
    top_layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    main_layout->addLayout(top_layout,Qt::AlignTop);
    left_layout = new QHBoxLayout;
    right_layout = new QHBoxLayout;
    top_layout->addStretch(2);
    top_layout->addLayout(left_layout,5);
    top_layout->addStretch(1);
    top_layout->addLayout(right_layout,5);
    top_layout->addStretch(2);
    left_layout->setAlignment(Qt::AlignJustify);
    right_layout->setAlignment(Qt::AlignJustify);
    sweep_area_layout = new QHBoxLayout;
    sweep_area_layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    //显示雷数时间等
    rest_mine_img = new QLabel;
    rest_mine_amount = new QLabel;
    pass_time_img = new QLabel;
    pass_time_amount = new QLabel;
    rest_mine_img->setText("剩余雷数：");
    mine_number = mine_amount;
    rest_mine_amount->setText(QString::number(mine_amount-flag_number));
    pass_time_img->setText("经过时间：");
    pass_time_amount->setText("0");
    left_layout->addStretch(1);
    left_layout->addWidget(rest_mine_img,2);
    left_layout->addStretch(1);
    left_layout->addWidget(rest_mine_amount,2);
    left_layout->addStretch(1);
    right_layout->addStretch(1);
    right_layout->addWidget(pass_time_img,2);
    right_layout->addStretch(1);
    right_layout->addWidget(pass_time_amount,2);
    right_layout->addStretch(1);
    //设置颜色
    rest_mine_amount->setStyleSheet(QString(COLORS[SKINS_CASE]));
    rest_mine_img->setStyleSheet(QString(COLORS[SKINS_CASE]));
    pass_time_amount->setStyleSheet(QString(COLORS[SKINS_CASE]));
    pass_time_img->setStyleSheet(QString(COLORS[SKINS_CASE]));

    //初始化资源文件
    //加载声音
    left_click = new QSoundEffect(this);
    right_click = new QSoundEffect(this);
    boom = new QSoundEffect(this);
    success = new QSoundEffect(this);
    load_Resources();

    //初始化地图
    this->width_amount = width_amount;
    this->height_amount = height_amount;
    init_Map(width_amount,height_amount,mine_amount);

    //开辟雷区
    sweep_area = new SweepArea(this,map,width_amount,height_amount);
    sweep_area->setFixedSize(width_amount*MINE_SIZE,height_amount*MINE_SIZE);
    main_layout->addLayout(sweep_area_layout,Qt::AlignTop);
    sweep_area_layout->addWidget(sweep_area);

    //设定计时器
    timer = new QTimer(sweep_area);
    timer->start(1000);
    //时间变化后修改时间数据
    connect(timer,&QTimer::timeout,this,&MainGame::time_Pass);
    //获取雷区的按键信息后，修改雷区数据
    connect(sweep_area,&SweepArea::mouseSignal,this,&MainGame::modify_Mine_Area);

    //设置字体
    font = new QFont("楷体");
    font->setPointSize(std::min(width(),height())/20);
    rest_mine_img->setFont(*font);
    rest_mine_amount->setFont(*font);
    pass_time_img->setFont(*font);
    pass_time_amount->setFont(*font);
}
MainGame::~MainGame()
{
    // delete ui;
    //释放地图空间
    for (int i = 0; i < height_amount; ++i) {
        delete[] map[i];
    }
    delete[] map;
}
void MainGame::load_Resources(){
    QString temp_image_path = QString(":/main/Resources/Images/%1/background.png").arg(SKINS[SKINS_CASE]);
    image_path = new QString(temp_image_path);
    back_ground = new QPixmap(*image_path);
    QString media_path = QString(":/main/Resources/Images/%1/blank_push.wav").arg(SKINS[SKINS_CASE]);
    QUrl media_path_url = QUrl::fromLocalFile(media_path);
    left_click->setSource(media_path_url);
    left_click->setVolume(1.0);
    media_path = QString(":/main/Resources/Images/%1/flag_change.wav").arg(SKINS[SKINS_CASE]);
    media_path_url = QUrl::fromLocalFile(media_path);
    right_click->setSource(media_path_url);
    right_click->setVolume(1.0);
    media_path = QString(":/main/Resources/Images/%1/boom.wav").arg(SKINS[SKINS_CASE]);
    media_path_url = QUrl::fromLocalFile(media_path);
    boom->setSource(media_path_url);
    boom->setVolume(1.0);
    media_path = QString(":/main/Resources/Images/%1/success.wav").arg(SKINS[SKINS_CASE]);
    media_path_url = QUrl::fromLocalFile(media_path);
    success->setSource(media_path_url);
    success->setVolume(1.0);
};
//地图初始化
void MainGame::init_Map(int width_amount,int height_amount,int mine_amount){
    //先开辟空间
    map = new int*[height_amount];
    for (int i = 0; i < height_amount; ++i) {
        map[i] = new int[width_amount];
    }
    //设定随机数，随机数生成器，范围类
    std::random_device randomSeed;
    std::mt19937 randomGenerator(randomSeed());
    std::uniform_int_distribution<int> distribution(0,width_amount*height_amount-1);
    //写个lambda给周围的数据加一（当然那个不能是雷）
    auto addNumber = [&](int x,int y){
        for(int i = x-1;i <= x+1;i++){
            for(int j = y-1;j <= y+1;j++){
                if((i>=0 && j >=0) && (i < height_amount && j < width_amount) && map[i][j]!=-1){
                    ++map[i][j];
                }
            }
        }
    };
    //先全部初始化为0;
    for (int i = 0; i < height_amount; ++i) {
        for (int j = 0; j < width_amount; ++j) {
            map[i][j] = 0;
        }
    }
    //开始设定雷和雷周围的数字
    for(int i = 0;i < mine_amount;){
        int position = distribution(randomGenerator);
        if(map[position/width_amount][position%width_amount] != -1)
        {
            //-1表示雷
            map[position/width_amount][position%width_amount] = -1;
            i++;
        }
    }
    //对周围的方格加一
    for (int i = 0; i < height_amount; ++i) {
        for (int j = 0; j < width_amount; ++j) {
            if(map[i][j]==-1) addNumber(i,j);
        }
    }
    //对格子增加20来表示这个格子还没有被打开
    for(int i = 0;i<height_amount;i++){
        for(int j = 0;j<width_amount;j++){
            map[i][j] += 20;
        }
    }
}
void MainGame::modify_Mine_Area(QMouseEvent *event){
    QPoint position = event->pos();
    int m_height = position.y()/MINE_SIZE;
    int m_width = position.x()/MINE_SIZE;
    // qDebug() << m_height << ' ' << m_width;
    if(event->button() == Qt::LeftButton){
        if(map[m_height][m_width]>=19 && map[m_height][m_width]<=28)
        {
            map[m_height][m_width] -= 20;
            //检测是否是空白格子，并打开周围的空格
            Open_Blanks(m_height,m_width);
        }
        //点完了是赢了
        int cnt=0;
        for(int i = 0;i<height_amount;i++){
            for(int j = 0;j<width_amount;j++){
                if(map[i][j]>=0 && map[i][j]<=8){
                    cnt++;
                }
            }
        }
        if(height_amount*width_amount - mine_number == cnt){
            gameRunning = false;
            winGame = true;
            success->play();
        }
        //判断是否点到了雷
        if(map[m_height][m_width]==-1 || map[m_height][m_width]==19){
            gameRunning = false;
            winGame = false;
            boom->play();
        }
        if(gameRunning == false)
        {
            QTimer::singleShot(500, [this]() {
                game_Over();
            });
        }
        else{
            left_click->play();
        }
    }else if(event->button() == Qt::RightButton){
        right_click->play();
        if(map[m_height][m_width]>=19 && map[m_height][m_width]<=28)
        {
            map[m_height][m_width]+=20;
            flag_number++;
            rest_mine_amount->setText(QString::number((mine_number-flag_number)>0?(mine_number-flag_number):0));
        }else if(map[m_height][m_width]>=39){
            map[m_height][m_width]-=20;
            flag_number--;
            rest_mine_amount->setText(QString::number((mine_number-flag_number)>0?(mine_number-flag_number):0));
        }
    }
    update();
};
void MainGame::Open_Blanks(int m_height,int m_width){
    //先判断是不是空白格子
    if(map[m_height][m_width] == 0){
        for(int i = m_height-1;i<=m_height+1;i++){
            for (int j = m_width-1; j <= m_width+1; ++j)
            {
                //首先不能越界，然后是没有打开的
                if(i>=0 && i < height_amount && j>=0 && j < width_amount
                    && map[i][j] >= 19 && map[i][j] <= 28){
                    map[i][j]-=20;
                    Open_Blanks(i,j);
                }
            }
        }
    }
};
void MainGame::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    //初始化绘图工具
    painter = new QPainter(this);

    //绘制背景图片
    painter->drawPixmap(0,0,width(),height(),*back_ground);

    // left_layout->setContentsMargins(0,0,width()*0.1,0);
    // right_layout->setContentsMargins(width()*0.1,0,0,0);
    // left_layout->setSpacing(width()*0.02);
    // right_layout->setSpacing(width()*0.02);
    if(cover_over) cover_over->setFixedSize(width(),height());

    font->setPointSize(std::min(width(),height())/20);
    rest_mine_img->setFont(*font);
    rest_mine_amount->setFont(*font);
    pass_time_img->setFont(*font);
    pass_time_amount->setFont(*font);

    update();
}
void MainGame::time_Pass(){
    time_count++;
    pass_time_amount->setText(QString::number(time_count));
}
void MainGame::game_Over(){
    int temp = (width()<height()?width():height());
    cover_over = new QWidget(this);
    game_over = new GameOver(this,time_count,winGame,temp/2,width_amount,height_amount,mine_number);
        cover_over_layout = new QVBoxLayout(cover_over);
        cover_over_layout->setAlignment(Qt::AlignCenter);
        cover_over_layout->addWidget(game_over);
        cover_over->show();
    game_over->show();
    timer->stop();

    emit overCreated();
};
