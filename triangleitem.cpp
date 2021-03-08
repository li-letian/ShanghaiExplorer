#include "triangleitem.h"
#include <QPainter>

TriangleItem::TriangleItem(QColor color,double distance,double scale_factor)
    :color_(color),
    distance_(distance),
    scale_factor_(scale_factor)
{
    this->setPos(0,-distance_);
    this->setTransformOriginPoint(0,distance_);
    this->MySetScale(scale_factor_);
}

QPainterPath TriangleItem::shape() const
{   
    QPainterPath path;
    path.moveTo(0,-100);
    path.lineTo(100,0);
    path.lineTo(-100,0);
    path.lineTo(0,-100);
    return path;
}

QRectF TriangleItem::boundingRect() const
{
    return QRectF(-100,-100,200,100);
}

void TriangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->fillPath(this->shape(),QBrush(color_));
}

void TriangleItem::MySetScale(double scale_factor)
{
    this->scale_factor_ = scale_factor;
    this->setScale(scale_factor_);
    this->setPos(0,-distance_/scale_factor_);
    this->setTransformOriginPoint(0,distance_/scale_factor_);
}

void TriangleItem::SetDistance(double distance)
{
    distance_ = distance;
    this->setPos(0, -distance_/scale_factor_);
    this->setTransformOriginPoint(0,distance_/scale_factor_);
}
