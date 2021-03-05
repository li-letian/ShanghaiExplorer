#include "compassview.h"
#include "triangleitem.h"

#include <QMouseEvent>
#include <QPixmap>
#include <QLabel>
#include <string>
#include <QTimer>
#include <cmath>
#define PI acos(-1)
using namespace std;


CompassView::CompassView(QWidget *parent):
    QGraphicsView(parent),
    compass_item_(nullptr),
    north_item_(nullptr)
{

}

void CompassView::paintAll()
{

}

void CompassView::updateReading()
{
    compass_reading = compass->reading();
    north_item_->setRotation(-compass_reading->azimuth());
}

void CompassView::updatePosition(const QGeoPositionInfo &pos)
{
    auto latitude=pos.coordinate().latitude();
    auto longitude=pos.coordinate().longitude();
}

void CompassView::Init()
{
    // Mark: 美化视图
    this->scene()->setBackgroundBrush(Qt::white);
    this->setStyleSheet("padding:0px;border:0px");

    // Debug: 测试坐标系统
    this->AddTriangleItem(30,1.0);

    // Mark: 添加指南针
    QPixmap pix_compass;
    pix_compass.load(":/compass.png");
    compass_item_ = this->scene()->addPixmap(pix_compass);
    compass_item_->setOffset(-compass_item_->boundingRect().width()/2,-compass_item_->boundingRect().height()/2);

    // Label Debug
//    auto label = new QLabel;
//    label->move(300,500);
//    label->resize(100,50);
//    label->setText(QString(std::to_string(this->width()).data()));
//    scene()->addWidget(label);

    // Mark: 添加指北
    QPixmap pix_north;
    pix_north.load(":/north-direction.png");
    north_item_ = this->scene()->addPixmap(pix_north);
    north_item_->setOffset(-north_item_->boundingRect().width()/2,-north_item_->boundingRect().height()/2);
    north_item_->setPos(width()/2-200,-height()/2+200);

    //添加指南针传感器
    compass = new QCompass(this);
    connect(compass, SIGNAL(readingChanged()), this, SLOT(updateReading()));
    compass->setDataRate(1);
    compass->start();
    compass_reading=compass->reading();


    //添加定位服务
    source = QGeoPositionInfoSource::createDefaultSource(this);
    if (source)
    {
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), this,SLOT(updatePosition(QGeoPositionInfo)));
        source->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
        source->startUpdates();
    }
}

void CompassView::AddTriangleItem(double rotation_angle,double scale_factor)
{
    auto item = new TriangleItem(QColor(236,200,53));
    item->MySetScale(scale_factor);
    item->setRotation(rotation_angle);
    this->scene()->addItem(item);
    triangles_.push_back(item);
}

void CompassView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);

    QPoint viewPos = event->pos();
    QPointF scenePos = mapToScene(viewPos);

    // Mark: 获取点击位置的item
    QGraphicsItem *item = scene()->itemAt(scenePos,QTransform());
    if(item != nullptr && item->type() == TRIANGEL_ITEM_TYPE)
    {
        RotateAll(30);
    }
}

void CompassView::RotateAll(double rotation_angle)
{
    for(auto triangle: triangles_)
    {
        triangle-> setRotation(triangle->rotation()+rotation_angle);
    }
    //north_item_->setRotation(north_item_->rotation()+rotation_angle);
}

double rad(double d) {
    return d *  PI/ 180.00; //角度转换成弧度
}

double algorithm(double longitude1, double latitude1, double longitude2, double latitude2) {
    double Lat1 = rad(latitude1); // 纬度

    double Lat2 = rad(latitude2);

    double a = Lat1 - Lat2;//两点纬度之差

    double b = rad(longitude1) - rad(longitude2); //经度之差

    double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(Lat1) * cos(Lat2) * pow(sin(b / 2), 2)));//计算两点距离的公式

    s = s * 6378137.0;//弧长乘地球半径（半径为米）

    s = round(s * 10000.0) / 10000.0;//精确距离的数值

    return s;

}




