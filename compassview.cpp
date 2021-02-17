#include "compassview.h"
#include "triangleitem.h"

#include <QMouseEvent>
#include <QPixmap>

CompassView::CompassView(QWidget *parent):
    QGraphicsView(parent)
{

}

void CompassView::Init()
{
    // Mark: 美化视图
    this->scene()->setBackgroundBrush(Qt::white);
    this->setStyleSheet("padding:0px;border:0px");

    // Debug: 测试坐标系统
    auto test_item = new TriangleItem;
    test_item->setPos(0,0);
    scene()->addItem(test_item);

    // Mark: 添加指南针
    QPixmap pix;
    pix.load(":/compass.png");

    auto compass_item = this->scene()->addPixmap(pix);
    compass_item->setPos(-compass_item->boundingRect().width()/2,-compass_item->boundingRect().height()/2);
}

void CompassView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);

    QPoint viewPos = event->pos();
    QPointF scenePos = mapToScene(viewPos);

    // Mark: 获取点击位置的item
    QGraphicsItem *item = scene()->itemAt(scenePos,QTransform());

}
