#ifndef COMPASSVIEW_H
#define COMPASSVIEW_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "triangleitem.h"
#include <vector>
#include <QLabel>
#include "sidebar.h"
using std::vector;

class CompassView:public QGraphicsView
{
    Q_OBJECT
public:
    explicit CompassView(QWidget *parent = 0);
    void Init();

    //www:侧边栏
    QString curLabel;//当前label
    QLabel* curLabelText;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent * event);
private:
    void AddTriangleItem(double rotation_angle=0,double scale_factor=1.0,QString text="");
    void RotateAll(double rotation_angle);
    QGraphicsPixmapItem* compass_item_;
    QGraphicsPixmapItem* north_item_;
    vector<TriangleItem*> triangles_;

    //绑定信息
    void bindInformation(TriangleItem* label,QString text);
    //www:侧边栏
    sideBar* sidebar;
    QPropertyAnimation* properAnimation;
    bool side_widget_flag;

};

#endif // COMPASSVIEW_H
