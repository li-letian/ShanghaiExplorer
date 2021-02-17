#include "compassview.h"
#include "triangleitem.h"

#include <QMouseEvent>
#include <QPixmap>
#include <QLabel>
#include <string>

CompassView::CompassView(QWidget *parent):
    QGraphicsView(parent),
    compass_item_(nullptr),
    north_item_(nullptr)
{

}

void CompassView::Init()
{
    // Mark: 美化视图
    this->scene()->setBackgroundBrush(Qt::white);
    this->setStyleSheet("padding:0px;border:0px");

    // Debug: 测试坐标系统
    this->AddTriangleItem(30,2.0);

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
    north_item_->setRotation(north_item_->rotation()+rotation_angle);
}
