#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QToolButton>
#include <QMenu>
#include <QShortcut>

void MainWindow::test01(){
    //创建一个工具栏
    QToolBar * toolBar = this->addToolBar("Tools");

    //创建一个工具按钮
    QToolButton* toolBtn = new QToolButton(this);
    toolBtn->setText("文件");
    toolBtn->setPopupMode(QToolButton::MenuButtonPopup);

    //创建一个菜单
    QMenu* menu = new QMenu(this);
    menu->addAction("选项1");
    menu->addAction("选项2");
    menu->addAction("选项3");

    //添加一个action，当点击它时窗口关闭
    QAction* quitAction = menu->addAction("退出(&X)");
    //1.为menu添加快捷键，因为quitAction->setShortcut无法做到这种效果[这里不需要做这一步否则QAction::eventFilter: Ambiguous shortcut overload: Ctrl+1]
    //QShortcut* shortcut = new QShortcut(QKeySequence("Ctrl+1"), menu);
    //connect(shortcut,&QShortcut::activated,qApp, &QApplication::quit);

    //2.为quitAction添加快捷键，并设置作用域让它不影响主窗口
    quitAction->setShortcut(QKeySequence("Ctrl+1"));//设定快捷键
    quitAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);//设定快捷键作用域，不影响到主窗口
    quitAction->setStatusTip("退出程序");

    //将退出动作的触发信号连接到qApplication的quit槽
    //connect(quitAction,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    //connect(quitAction, &QAction::triggered, this, &MainWindow::testSlot);

    //将菜单设置为工具按钮的下拉菜单
    toolBtn->setMenu(menu);
    //menu->show();

    //添加工具按钮到工具栏中
    toolBar->addWidget(toolBtn);

}
void MainWindow::test02(){
    QMenuBar * menubar = new QMenuBar(this);//创建菜单栏

    QMenu *menu_test;

    menu_test = new QMenu("menu11");//创建菜单

    QAction * action_1;

    action_1 = new QAction("act1",menu_test);//创建动作


    menu_test->addAction(action_1);
    //1.为menu_test添加快捷键，因为action_1->setShortcut无法做到这种效果
    QShortcut* shortcut = new QShortcut(QKeySequence("Ctrl+1"), menu_test);
    connect(shortcut,&QShortcut::activated,qApp, &QApplication::quit);
    //2.为action_1添加快捷键，并设置作用域让它不影响主窗口
    action_1->setShortcut(QKeySequence("Ctrl+1"));//设定快捷键
    action_1->setShortcutContext(Qt::WidgetWithChildrenShortcut);//设定快捷键作用域，不影响到主窗口

    connect(action_1 , &QAction::triggered , qApp, &QApplication::quit);//关联槽函数

    //action_1->setShortcut(tr("Ctrl+1"));//设定快捷键

    //action_1->setShortcut(0);//如果写了这句就可以取消快捷键

    menubar->addMenu(menu_test);


}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    test01();
}

MainWindow::~MainWindow()
{
    delete ui;
}
