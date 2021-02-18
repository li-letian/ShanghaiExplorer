#ifndef COMPASSVIEW_H
#define COMPASSVIEW_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "triangleitem.h"
#include "dataloader.h"
#include "detailwidget.h"
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
private:
    void paintAll();
    void AddTriangleItem(double rotation_angle=0,double scale_factor=1.0);
    void RotateAll(double rotation_angle);
    QGraphicsPixmapItem* compass_item_;
    QGraphicsPixmapItem* north_item_;
    vector<TriangleItem*> triangles_;
    QCompass *compass;
    QCompassReading *compass_reading;
    QGeoPositionInfoSource* source;
    DataLoader* loader;
    DetailWidget* detail;
};

#endif // COMPASSVIEW_H
