#ifndef TRIANGLEITEM_H
#define TRIANGLEITEM_H

#include <QGraphicsItem>

// Mark: constants
constexpr int TRIANGEL_ITEM_TYPE = 0;
constexpr double BASE_DISTANCE = 300;

class TriangleItem : public QGraphicsItem
{
public:
    TriangleItem(QColor color = Qt::white, double distance = BASE_DISTANCE, double scale_factor = 1.0);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int type() const override { return TRIANGEL_ITEM_TYPE; }

    void MySetScale(double scale_factor = 1.0);
    double MyGetScale() { return scale_factor_; }

    void SetDistance(double distance);
    double GetDistance() { return distance_; }

    double GetZhijiaobianLength() { return 200 * scale_factor_; }
    int index;

private:
    QColor color_;
    double distance_;
    double scale_factor_;
};

#endif // TRIANGLEITEM_H
