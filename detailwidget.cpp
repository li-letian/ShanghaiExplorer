#include "detailwidget.h"
#include "dataloader.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QScreen>
#include <QLabel>
#include <QSize>

DetailWidget::DetailWidget(QWidget *parent) :
    QWidget(parent)
{
    auto screens = QGuiApplication::screens();
    auto screen=screens.at(0)->availableGeometry();

    setStyleSheet("background-color:rgb(255,255,255,220);color:black;font:20pt;padding:0px;border:0px");

    //暂无图片处理
    pic=new QLabel(this);

    label=new QLabel(this);
    QFont font("宋体",20,75);
    label->setFont(font);
    label->setFixedWidth(screen.width()*3/4);
    label->move(screen.width()/8,screen.width()/4);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    connect(this,SIGNAL(clicked()),this,SLOT(hideDetail()));
}

void DetailWidget::updateText(double dis,QString name,QString address,QString intro)
{
    //图片功能暂缺
    label->setText("建筑名："+name+"\n\n地址："+address+"\n\n距离："+QString::number(dis)+"米\n\n简介："+intro);
}

void DetailWidget::mouseReleaseEvent(QMouseEvent * ev)
{
   emit clicked();
}

void DetailWidget::hideDetail()
{
    this->hide();
}

DetailWidget::~DetailWidget()
{
}
