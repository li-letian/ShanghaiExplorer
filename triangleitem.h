#ifndef TRIANGLEITEM_H
#define TRIANGLEITEM_H

#include <QGraphicsItem>

// Mark: constants
constexpr int TRIANGEL_ITEM_TYPE = 0;
constexpr int BASE_DISTANCE = 300;
constexpr int DELTA = 300;

class TriangleItem:public QGraphicsItem
{
public:
    TriangleItem(QColor color_=Qt::white,int delta_num = 0);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int type() const override {return TRIANGEL_ITEM_TYPE;}

    void MySetScale(double scale_factor = 1.0);
    void MySetPos(double rotation_angle=0,double scale_factor=1.0,int delta_num=0);

    int GetDeltaNum()const {return delta_num_;}
    int SetDeltaNum(const int delta_num) {delta_num_ = delta_num;}

    double Distance(){return BASE_DISTANCE+DELTA*delta_num_;}
    int index;
private:
    QColor color_;
    int delta_num_;
};

#endif // TRIANGLEITEM_H
