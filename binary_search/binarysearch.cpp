#include "binarysearch.h"
#include "./ui_binarysearch.h"

#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

const int BOX_WIDTH = 60;
const int BOX_HEIGHT = 40;
const int SPACING = 10;

BinarySearch::BinarySearch(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BinarySearch)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    initScene();
    createPointers();

    connect(ui->btnStart, &QPushButton::clicked, this, &BinarySearch::onSearchStart);
    connect(ui->btnNext, &QPushButton::clicked, this, &BinarySearch::onNextStep);
}

BinarySearch::~BinarySearch()
{
    delete ui;
}

void BinarySearch::initScene()
{
    // 创建数组元素
    for(int i=0; i<data.size(); ++i){
        QGraphicsRectItem *box = new QGraphicsRectItem(
            i*(BOX_WIDTH+SPACING), 0, BOX_WIDTH, BOX_HEIGHT);
        box->setBrush(QColor(240,240,240));
        scene->addItem(box);
        boxes << box;

        QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem(QString::number(data[i]), box);
        text->setPos(box->rect().center() - text->boundingRect().center());
        numbers << text;
    }
}

void BinarySearch::createPointers() {
    // 使用AnimatedEllipseItem创建指针
    leftPtr = new AnimatedEllipseItem(-10, BOX_HEIGHT+10, 20, 20);
    leftPtr->setBrush(Qt::blue);
    scene->addItem(leftPtr);

    rightPtr = new AnimatedEllipseItem(-10, BOX_HEIGHT+10, 20, 20);
    rightPtr->setBrush(Qt::red);
    scene->addItem(rightPtr);

    midPtr = new AnimatedEllipseItem(-10, -30, 20, 20);
    midPtr->setBrush(Qt::green);
    scene->addItem(midPtr);

    resetSearch();
}

void BinarySearch::updatePointers() {
    QParallelAnimationGroup *group = new QParallelAnimationGroup;

    QPropertyAnimation *leftAnim = new QPropertyAnimation(leftPtr, "pos");
    leftAnim->setStartValue(leftPtr->pos());  // 显式设置起始值
    QPointF boxLeftPos = boxes[left]->mapToScene(boxes[left]->rect().center());
    leftAnim->setEndValue(boxLeftPos + QPointF(0, -20));
    qDebug() << "【start:" << leftPtr->pos()
             << "\nend:" << boxLeftPos
             << "】";
    leftAnim->setDuration(500);  // 单独设置时长
    group->addAnimation(leftAnim);

    QPropertyAnimation *rightAnim = new QPropertyAnimation(rightPtr, "pos");
    rightAnim->setStartValue(rightPtr->pos());  // 显式设置起始值
    QPointF boxRightPos = boxes[right]->mapToScene(boxes[right]->rect().center());
    rightAnim->setEndValue(boxRightPos + QPointF(0, -20));
    rightAnim->setDuration(500);  // 单独设置时长
    group->addAnimation(rightAnim);

    if (mid >=0 && mid < data.size()) {
        QPropertyAnimation *midAnim = new QPropertyAnimation(midPtr, "pos");
        midAnim->setStartValue(midPtr->pos());  // 显式设置起始值
        QPointF boxMidPos = boxes[mid]->mapToScene(boxes[mid]->rect().center());
        midAnim->setEndValue(boxMidPos + QPointF(0, -20));
        midAnim->setDuration(500);  // 单独设置时长
        group->addAnimation(midAnim);
    }

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void BinarySearch::onSearchStart()
{
    target = ui->editTarget->text().toInt();
    resetSearch();
    ui->lblStatus->setText("搜索开始");
}

void BinarySearch::onNextStep()
{
    performSearchStep();
}

void BinarySearch::resetSearch()
{
    //将之前的黄色标记清除
    if(mid >=0 && mid < data.size()){
        boxes[mid]->setBrush(QColor(240,240,240));
    }
    currentStep = 0;
    left = 0;
    right = data.size() -1;
    mid = left + (right - left)/2;
    updatePointers();
}

void BinarySearch::performSearchStep()
{
    if(left > right){
        QMessageBox::information(this, "搜索失败", "未找到目标值");
        return;
    }

    ui->lblStatus->setText(QString("步骤%1: 检查位置%2 (值=%3)")
                               .arg(++currentStep).arg(mid).arg(data[mid]));

    if(data[mid] == target){
        QMessageBox::information(this, "搜索成功", QString("找到目标值在位置%1").arg(mid));
        boxes[mid]->setBrush(Qt::yellow);
        return;
    }
    else if(data[mid] < target){
        left = mid +1;
    }
    else{
        right = mid -1;
    }
    mid = left + (right - left)/2;// mid是下一个中间结点的值

    updatePointers();
}
