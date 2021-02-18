#ifndef TRIANGLEITEM_H
#define TRIANGLEITEM_H

#include <QGraphicsItem>

// Mark: constants
constexpr int TRIANGEL_ITEM_TYPE = 0;
constexpr int DISTANCE_FROM_ORIGIN = 350;

class TriangleItem:public QGraphicsItem
{
public:
    int index;
    TriangleItem(QColor color_=Qt::white);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int type() const override {return TRIANGEL_ITEM_TYPE;}

    void MySetScale(double scale_factor = 1.0);
private:
    QColor color_;
};

#endif // TRIANGLEITEM_H
