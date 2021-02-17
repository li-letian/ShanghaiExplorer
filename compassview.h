#ifndef COMPASSVIEW_H
#define COMPASSVIEW_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "triangleitem.h"
#include <vector>

using std::vector;

class CompassView:public QGraphicsView
{
    Q_OBJECT
public:
    explicit CompassView(QWidget *parent = 0);
    void Init();
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    void AddTriangleItem(double rotation_angle=0,double scale_factor=1.0);
    void RotateAll(double rotation_angle);
    QGraphicsPixmapItem* compass_item_;
    QGraphicsPixmapItem* north_item_;
    vector<TriangleItem*> triangles_;
};

#endif // COMPASSVIEW_H
