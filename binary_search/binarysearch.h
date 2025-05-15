#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

// 自定义支持动画的椭圆项
class AnimatedEllipseItem : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    explicit AnimatedEllipseItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr)
        : QObject(nullptr), QGraphicsEllipseItem(x, y, w, h, parent) {}
};

QT_BEGIN_NAMESPACE
namespace Ui {
class BinarySearch;
}
QT_END_NAMESPACE

class BinarySearch : public QWidget
{
    Q_OBJECT

public:
    BinarySearch(QWidget *parent = nullptr);
    ~BinarySearch();

private slots:
    void onSearchStart();
    void onNextStep();

private:
    Ui::BinarySearch *ui;
    QGraphicsScene *scene;
    QList<int> data = {1,3,5,7,9,11,13,15,17,19};

    // 图形项
    QList<QGraphicsRectItem*> boxes;
    QList<QGraphicsSimpleTextItem*> numbers;
    AnimatedEllipseItem *leftPtr, *rightPtr, *midPtr;

    // 查找状态
    int currentStep = 0;
    int target = 0;
    int left = 0;
    int right = 9;
    int mid = -1;

    void initScene();
    void createPointers();
    void updatePointers();
    void resetSearch();
    void performSearchStep();
};
#endif // BINARYSEARCH_H
