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

    // Mark: 添加指南针
    QPixmap pix;
    pix.load(":/compass.png");
    this->scene()->addPixmap(pix);
}

void CompassView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);

    QPoint viewPos = event->pos();
    QPointF scenePos = mapToScene(viewPos);

    // Mark: 获取点击位置的item
    QGraphicsItem *item = scene()->itemAt(scenePos,QTransform());

}
