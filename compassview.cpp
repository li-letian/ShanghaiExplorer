#include "compassview.h"
#include "triangleitem.h"
#include "detailwidget.h"
#include "dataloader.h"
#include "sidebarwidget.h"

#include <QMouseEvent>
#include <QPixmap>
#include <QLabel>
#include <string>
#include <QTimer>
#include <QPropertyAnimation>
#include <cstdlib>
#include <QPushButton>
#include <QGuiApplication>
#include <QScreen>
#include <cmath>
#include <algorithm>

using namespace std;

CompassView::CompassView(QWidget *parent) :
    QGraphicsView(parent),
    compass_item_(nullptr),
    north_item_(nullptr)
{
}

void CompassView::paintAll()
{
    auto azimuth=compass_reading->azimuth();

    for(auto item:triangles_)
    {
        auto index=item->index;
        auto la1=latitude;
        auto lo1=longitude;
        auto la2=loader->latitude(index).toDouble();
        auto lo2=loader->longitude(index).toDouble();
        auto dis0=algorithm(lo1,la1,lo2,la2);
        auto dis1=algorithm(lo1,la2,lo2,la2);
        auto base_angle=asin(dis1/dis0)*180.0/PI;
        double ang=0;
        if(la2>la1)
        {
            if(lo2<lo1)
            {
                ang=360.0-base_angle;
            }
            else if(lo2>lo1)
            {
                ang=base_angle;
            }
            else
            {
                ang=0.0;
            }
        }
        else if(la2<la1)
        {
            if(lo2<lo1)
            {
                ang=180.0+base_angle;
            }
            else if(lo2>lo1)
            {
                ang=180.0-base_angle;
            }
            else
            {
                ang=180.0;
            }
        }
        else
        {
            if(lo2<lo1)
            {
                ang=270.0;
            }
            else if(lo2>lo1)
            {
                ang=90.0;
            }
        }
        ang-=azimuth;
        while(ang<0.0)
        {
            ang+=360.0;
        }
        while(ang>360.0)
        {
            ang-=360.0;
        }
        item->setRotation(ang);
    }
//    std::sort(triangles_.begin(),triangles_.end(),[=](TriangleItem* const A,TriangleItem* const B){return A->rotation()<B->rotation();});
//    int len=triangles_.size();
//    for(int i=0;i<len;i++)
//    {

//    }

}

void CompassView::updateReading()
{
    compass_reading = compass->reading();
    north_item_->setRotation(-compass->reading()->azimuth());
    paintAll();
}

void CompassView::updatePosition(const QGeoPositionInfo &pos)
{
    longitude = pos.coordinate().longitude();
    latitude = pos.coordinate().latitude();
    paintAll();
}

void CompassView::Init(DataLoader *dataloader)
{
    auto screens = QGuiApplication::screens();
    auto screen = screens.at(0)->availableGeometry();

    loader = dataloader;
    // Mark: 美化视图
    this->scene()->setBackgroundBrush(Qt::white);
    this->setStyleSheet("padding:0px;border:0px");

    //加入建筑
    AddTriangles();

    // Mark: 添加指南针
    QPixmap pix_compass;
    pix_compass.load(":/compass.png");
    compass_item_ = this->scene()->addPixmap(pix_compass);
    compass_item_->setOffset(-compass_item_->boundingRect().width() / 2, -compass_item_->boundingRect().height() / 2);

    // Mark: 添加指北
    QPixmap pix_north;
    pix_north.load(":/north-direction.png");
    north_item_ = this->scene()->addPixmap(pix_north);
    north_item_->setOffset(-north_item_->boundingRect().width() / 2, -north_item_->boundingRect().height() / 2);
    north_item_->setPos(width() / 2 - 200, -height() / 2 + 200);

    //添加指南针传感器
    compass = new QCompass(this);
    connect(compass, SIGNAL(readingChanged()), this, SLOT(updateReading()));
    compass->setDataRate(1);
    compass->start();
    compass_reading = compass->reading();

    //添加定位服务
    source = QGeoPositionInfoSource::createDefaultSource(this);
    if (source)
    {
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(updatePosition(QGeoPositionInfo)));
        source->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
        source->startUpdates();
    }

    //添加介绍页面
    detail = new DetailWidget(this);
    detail->hide();

    //添加侧边栏
    side_bar = new SideBarWidget(this);
    side_bar->init(loader);

    auto button = new QPushButton(this);
    button->move(5, 5);
    QIcon icon(QPixmap(":/button.png"));
    button->setIcon(icon);
    button->setIconSize(QSize(screen.width() /10, screen.height() / 10));
    button->show();
    connect(button, SIGNAL(clicked()), side_bar, SLOT(fade()));
    connect(side_bar, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(changeLabel(QListWidgetItem *)));
}

void CompassView::changeLabel(QListWidgetItem *item)
{
    loader->current_label = item->text();
    AddTriangles();
}

void CompassView::AddTriangles()
{
    for (auto item : triangles_)
    {
        this->scene()->removeItem(item);
        delete item;
    }
    triangles_.clear();
    int len = loader->size();
    int delta = 36;
    for (int index = 0; index < len; index++)
    {
        if (loader->check(index))
        {
            this->AddTriangleItem(delta * index, 1.0, index);
        }
    }
}

void CompassView::AddTriangleItem(double rotation_angle, double scale_factor, int index)
{
    auto color_id = rand() % 5;
    auto item = new TriangleItem(QColor(color[color_id][0], color[color_id][1], color[color_id][2]));
    item->MySetScale(scale_factor);
    item->setRotation(rotation_angle);
    item->index = index;
    this->scene()->addItem(item);
    triangles_.push_back(item);
}

void CompassView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    QPoint viewPos = event->pos();
    QPointF scenePos = mapToScene(viewPos);

    // Mark: 获取点击位置的item
    QGraphicsItem *item = scene()->itemAt(scenePos, QTransform());
    if (item != nullptr && item->type() == TRIANGEL_ITEM_TYPE)
    {
        int index = dynamic_cast<TriangleItem *>(item)->index;
        detail->updateText(loader->name(index), loader->address(index), loader->intro(index));
        detail->show();
    }
}

void CompassView::RotateAll(double rotation_angle)
{
    for (auto triangle : triangles_)
    {
        triangle->setRotation(triangle->rotation() + rotation_angle);
    }
    north_item_->setRotation(north_item_->rotation()+rotation_angle);
}
