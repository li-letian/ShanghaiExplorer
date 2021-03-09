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
#include <cmath>

#define PI (acos(-1))
using namespace std;

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

public:

    double rad(double d)
    {
        return d * PI / 180.00; //角度转换成弧度
    }

    double algorithm(double longitude1, double latitude1, double longitude2, double latitude2)
    {
        double Lat1 = rad(latitude1); // 纬度

        double Lat2 = rad(latitude2);

        double a = Lat1 - Lat2; //两点纬度之差

        double b = rad(longitude1) - rad(longitude2); //经度之差

        double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(Lat1) * cos(Lat2) * pow(sin(b / 2), 2))); //计算两点距离的公式

        s = s * 6378137.0; //弧长乘地球半径（半径为米）

        s = round(s * 10000.0) / 10000.0; //精确距离的数值

        return s;
    }

};

#endif // COMPASSVIEW_H
