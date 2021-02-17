#include "triangleitem.h"
#include <QPainter>

TriangleItem::TriangleItem()
{

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
    return QRectF(0,0,200,100);
}

void TriangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->fillPath(this->shape(),QBrush(QColor("blue")));
}
