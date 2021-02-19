#ifndef COMPASSVIEW_H
#define COMPASSVIEW_H

#include "triangleitem.h"
#include "dataloader.h"
#include "detailwidget.h"
#include "sidebarwidget.h"

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QCompass>
#include <QCompassReading>
#include <QLabel>
#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>
#include <QGeoCoordinate>
#include <QStringList>

using std::vector;

class CompassView:public QGraphicsView
{
    Q_OBJECT
public:
    explicit CompassView(QWidget *parent = 0);
    void Init(DataLoader* dataloader);
protected:
    void mousePressEvent(QMouseEvent *event);
public slots:
    void updateReading();
    void updatePosition(const QGeoPositionInfo &pos);
    void changeLabel(QListWidgetItem *item);
private:
    void paintAll();
    void AddTriangles();
    void AddTriangleItem(double rotation_angle=0,double scale_factor=1.0,int index=0);
    void RotateAll(double rotation_angle);
    QGraphicsPixmapItem* compass_item_;
    QGraphicsPixmapItem* north_item_;
    vector<TriangleItem*> triangles_;
    QCompass *compass;
    QCompassReading *compass_reading;
    QGeoPositionInfoSource* source;
    double latitude=0.0;
    double longitude=0.0;
    DataLoader* loader;
    DetailWidget* detail;
    SideBarWidget* side_bar;

    int color[5][3]={{236,200,53},{235,98,66},{118,170,209},{34,172,56},{159,160,160},};
};

#endif // COMPASSVIEW_H
