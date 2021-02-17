#ifndef TRIANGLEITEM_H
#define TRIANGLEITEM_H

#include <QGraphicsItem>

class TriangleItem:public QGraphicsItem
{
public:
    TriangleItem();
    QRectF boundingRect() const;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:

};

#endif // TRIANGLEITEM_H
