#include "compassview.h"

#include <QMouseEvent>
#include <QGraphicsItem>
#include <QDebug>
#include <QLabel>

CompassView::CompassView(QWidget *parent):
    QGraphicsView(parent)
{
    label = new QLabel;
    label->move(200, 200);
    label->resize(200, 50);
    label->setText(QString("点击次数"));
    label->setFont(QFont("宋体", 18));
    label->setAlignment(Qt::AlignCenter);
}

void CompassView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);

    QPoint viewPos = event->pos();
    QPointF scenePos = mapToScene(viewPos);

    // 获取点击位置的item
    QGraphicsItem *item = scene()->itemAt(scenePos,QTransform());

}
