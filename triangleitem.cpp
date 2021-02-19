#include "triangleitem.h"
#include <QPainter>

TriangleItem::TriangleItem(QColor color, int delta_num)
    : color_(color),
      delta_num_(delta_num)
{
    this->setPos(0, -Distance());
    this->setTransformOriginPoint(0, Distance());
    index = 0;
}

QPainterPath TriangleItem::shape() const
{
    QPainterPath path;
    path.moveTo(0, -100);
    path.lineTo(100, 0);
    path.lineTo(-100, 0);
    path.lineTo(0, -100);
    return path;
}

QRectF TriangleItem::boundingRect() const
{
    return QRectF(-100, -100, 200, 100);
}

void TriangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->fillPath(this->shape(), QBrush(color_));
}

void TriangleItem::MySetScale(double scale_factor)
{
    this->setScale(scale_factor);
    this->setPos(0, -Distance() / scale_factor);
    this->setTransformOriginPoint(0, Distance() / scale_factor);
}

void TriangleItem::MySetPos(double rotation_angle, double scale_factor, int delta_num)
{
    delta_num_ = delta_num;
    this->setPos(0, -Distance());
    this->setTransformOriginPoint(0, Distance());
    this->MySetScale(scale_factor);
    this->setRotation(rotation_angle);
}
