#include "compassview.h"
#include "triangleitem.h"

#include <QMouseEvent>
#include <QPixmap>
#include <QLabel>
#include <string>

#include <QRadioButton>
#include <QMessageBox>
#include "dataloader.h"
#include "sidebar.h"
#include <QHBoxLayout>

CompassView::CompassView(QWidget *parent):
    QGraphicsView(parent),
    compass_item_(nullptr),
    north_item_(nullptr)
{


}

void CompassView::Init()
{
    //侧边栏相关
    this->sidebar=new sideBar(this);
    this->curLabelText=new QLabel(this);

    //向sidebar中添加按钮
    DataLoader dataLoader;
    dataLoader.load();
    int j=0;
    for (auto i=dataLoader.labels.begin();i!=dataLoader.labels.end();++i,++j){
        //增加i
        QRadioButton* button=new QRadioButton(this->sidebar);
        button->setText(*i);
        button->setGeometry(0,30*j,button->geometry().width(),button->geometry().height());

        connect(button,&QRadioButton::toggled,this,[=](){
            //更改所选择标签
            this->curLabel=button->text();
            qDebug()<<curLabel;
            //this->curLabelText->setText(*i);
        });

        if (j==0) {
            this->curLabel=*i;
            //curLabelText->setText(*i);
        }
    }


    //动画效果初始化
    this->side_widget_flag=true;
    this->sidebar->move(this->rect().width()+this->sidebar->width(),0);
    this->properAnimation=new QPropertyAnimation(sidebar,"geometry");
    properAnimation->setEasingCurve(QEasingCurve::InOutQuint);
    properAnimation->setDuration(1000);


    // Mark: 美化视图
    this->scene()->setBackgroundBrush(Qt::white);
    this->setStyleSheet("padding:0px;border:0px");

    // Debug: 测试坐标系统
    this->AddTriangleItem(30,2.0,"Chang\r\nNothing can be better than me.\r\nYes.");

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

void CompassView::AddTriangleItem(double rotation_angle,double scale_factor,QString text)
{
    auto item = new TriangleItem(QColor(236,200,53));
    this->bindInformation(item,text);
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
        //旋转指定角度
        RotateAll(30);

    }
}

void CompassView::mouseDoubleClickEvent(QMouseEvent * event)
{
    Q_UNUSED(event)
    if(side_widget_flag){
        //如果被隐藏，则需要显示
        properAnimation->setStartValue(QRect(this->rect().width(),0,this->sidebar->width(),this->sidebar->height()));
        properAnimation->setEndValue(QRect(this->rect().width()-this->sidebar->width(),0,this->sidebar->width(),this->sidebar->height()));
        properAnimation->start();
        side_widget_flag=!side_widget_flag;
    }
    else{
        properAnimation->setStartValue(QRect(this->rect().width()-this->sidebar->width(),0,this->sidebar->width(),this->sidebar->height()));
        properAnimation->setEndValue(QRect(this->rect().width(),0,this->sidebar->width(),this->sidebar->height()));
        properAnimation->start();
        side_widget_flag = !side_widget_flag;
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

//将label绑定上相应的信息text
void CompassView::bindInformation(TriangleItem* place,QString text){
    //为该地点绑定一段文本
    place->setToolTip(text);
}
