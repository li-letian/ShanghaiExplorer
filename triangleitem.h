#ifndef TRIANGLEITEM_H
#define TRIANGLEITEM_H

#include <QGraphicsItem>

constexpr int TRIANGEL_ITEM_TYPE = 0;

class TriangleItem:public QGraphicsItem
{
public:
    TriangleItem();
    QRectF boundingRect() const;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int type() const override {return TRIANGEL_ITEM_TYPE;}
private:

};

#endif // TRIANGLEITEM_H
