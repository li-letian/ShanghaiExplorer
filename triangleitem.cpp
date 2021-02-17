#include "triangleitem.h"
#include <QPainter>

TriangleItem::TriangleItem(QColor color)
    :color_(color)
{
    this->setPos(0,-DISTANCE_FROM_ORIGIN);
    this->setTransformOriginPoint(0,DISTANCE_FROM_ORIGIN);
}

QPainterPath TriangleItem::shape() const
{   
    QPainterPath path;
    path.moveTo(0,-50);
    path.lineTo(100,50);
    path.lineTo(-100,50);
    path.lineTo(0,-50);
    return path;
}

QRectF TriangleItem::boundingRect() const
{
    return QRectF(-100,-50,200,100);
}

void TriangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->fillPath(this->shape(),QBrush(color_));

}

void TriangleItem::MySetScale(double scale_factor)
{
    this->setScale(scale_factor);
    this->setPos(0,-DISTANCE_FROM_ORIGIN/scale_factor);
    this->setTransformOriginPoint(0,DISTANCE_FROM_ORIGIN/scale_factor);
}
