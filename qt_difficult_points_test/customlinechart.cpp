// customlinechart.cpp
#include "customlinechart.h"
#include <QFontMetrics>
#include <QDebug>

CustomLineChart::CustomLineChart(QWidget *parent)
    : QWidget(parent), m_isMouseOver(false), m_quadtree(nullptr)
{
    setMouseTracking(true);
}

CustomLineChart::~CustomLineChart()
{
    delete m_quadtree;
}

void CustomLineChart::addDataSet(const DataSet& dataSet)
{
    m_dataSets.append(dataSet);

    // 构建四叉树
    if (m_quadtree == nullptr) {
        int margin = 20;
        QRectF bounds(margin, margin, width() - 2 * margin, height() - 2 * margin);
        qDebug() << "width():" << width();
        qDebug() << "height():" << height();
        qDebug() << bounds;
        m_quadtree = new QuadTreeNode(bounds, 4);
    }

    int margin = 20;
    int xAxisLength = width() - 2 * margin;
    int yAxisLength = height() - 2 * margin;

    for (const auto& point : dataSet.points) {
        // 将比例值转换为实际坐标
        DataPoint actualPoint;
        actualPoint.x = margin + point.x * xAxisLength;
        actualPoint.y = height() - margin - point.y * yAxisLength;
        m_quadtree->insert(actualPoint);
    }

    update();
}

void CustomLineChart::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawAxes(painter);
    drawLines(painter);
    if (m_isMouseOver) {
        drawDataPointTip(painter);
    }
}

void CustomLineChart::mouseMoveEvent(QMouseEvent *event)
{
    m_isMouseOver = true;
    m_mousePos = event->pos();
    //qDebug() << "执行mouseMoveEvent" << m_mousePos;
    update();
}

void CustomLineChart::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_isMouseOver = false;
    update();
}

void CustomLineChart::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    rebuildQuadtree();
}

void CustomLineChart::rebuildQuadtree()
{
    delete m_quadtree;
    m_quadtree = nullptr;

    int margin = 20;
    QRectF bounds(margin, margin, width() - 2 * margin, height() - 2 * margin);
    qDebug() << "width():" << width();
    qDebug() << "height():" << height();
    qDebug() << bounds;
    m_quadtree = new QuadTreeNode(bounds, 4);

    int xAxisLength = width() - 2 * margin;
    int yAxisLength = height() - 2 * margin;

    for (const auto& dataSet : m_dataSets) {
        for (const auto& point : dataSet.points) {
            // 将比例值转换为实际坐标
            DataPoint actualPoint;
            actualPoint.x = margin + point.x * xAxisLength;
            actualPoint.y = height() - margin - point.y * yAxisLength;
            m_quadtree->insert(actualPoint);
        }
    }
}

void CustomLineChart::drawAxes(QPainter& painter)
{
    int margin = 20;
    int xAxisLength = width() - 2 * margin;
    int yAxisLength = height() - 2 * margin;

    // 绘制x轴
    painter.drawLine(margin, height() - margin, width() - margin, height() - margin);
    // 绘制y轴
    painter.drawLine(margin, margin, margin, height() - margin);

    // 绘制x轴刻度和标签
    int numXTicks = 5;
    for (int i = 0; i <= numXTicks; ++i) {
        int x = margin + i * xAxisLength / numXTicks;
        painter.drawLine(x, height() - margin, x, height() - margin + 5);
        QString label = QString::number(i);
        QFontMetrics fm(painter.font());
        int labelWidth = fm.horizontalAdvance(label);
        painter.drawText(x - labelWidth / 2, height() - margin + 20, label);
    }

    // 绘制y轴刻度和标签
    int numYTicks = 5;
    for (int i = 0; i <= numYTicks; ++i) {
        int y = height() - margin - i * yAxisLength / numYTicks;
        painter.drawLine(margin, y, margin - 5, y);
        QString label = QString::number(i);
        QFontMetrics fm(painter.font());
        int labelWidth = fm.horizontalAdvance(label);
        painter.drawText(margin - labelWidth - 10, y + fm.ascent() / 2, label);
    }
}

void CustomLineChart::drawLines(QPainter& painter)
{
    int margin = 20;
    int xAxisLength = width() - 2 * margin;
    int yAxisLength = height() - 2 * margin;

    for (const auto& dataSet : m_dataSets) {
        painter.setPen(QPen(dataSet.color, 2));
        for (int i = 0; i < dataSet.points.size() - 1; ++i) {
            const DataPoint& p1 = dataSet.points[i];
            const DataPoint& p2 = dataSet.points[i + 1];
            int x1 = margin + static_cast<int>(p1.x * xAxisLength);
            int y1 = height() - margin - static_cast<int>(p1.y * yAxisLength);
            int x2 = margin + static_cast<int>(p2.x * xAxisLength);
            int y2 = height() - margin - static_cast<int>(p2.y * yAxisLength);
            painter.drawLine(x1, y1, x2, y2);
        }
    }
}

void CustomLineChart::drawDataPointTip(QPainter& painter)
{
    int margin = 20;
    int xAxisLength = width() - 2 * margin;
    int yAxisLength = height() - 2 * margin;

    QRectF queryRange(m_mousePos.x() - 5, m_mousePos.y() - 5, 10, 10);
    QVector<DataPoint> foundPoints;
    if (m_quadtree != nullptr) {
        m_quadtree->query(queryRange, foundPoints);
    }

    for (const auto& point : foundPoints) {
        // 将实际坐标转换回比例值
        double scaleX = (point.x - margin) / static_cast<double>(xAxisLength);
        double scaleY = (height() - margin - point.y) / static_cast<double>(yAxisLength);
        qDebug() << "包含该点";
        QString tip = QString("(%1, %2)").arg(scaleX).arg(scaleY);
        QFontMetrics fm(painter.font());
        int tipWidth = fm.horizontalAdvance(tip);
        int tipHeight = fm.height();
        painter.fillRect(point.x + 5, point.y - tipHeight - 5, tipWidth + 10, tipHeight + 10, Qt::white);
        painter.drawText(point.x + 10, point.y - 5, tip);
    }
}
