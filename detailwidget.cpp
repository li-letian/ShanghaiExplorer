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

    setStyleSheet("background-color:rgb(255,255,255,220);color:black;font:20pt;");

    //记得处理图片
    pic=new QLabel(this);

    label=new QLabel(this);
    QFont font("宋体",20,75);
    label->setFont(font);
    label->setFixedWidth(screen.width()*3/4);
    label->move(screen.width()/8,screen.width()/4);
    label->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    connect(this,SIGNAL(clicked()),this,SLOT(hideDetail()));
}

void DetailWidget::updateText(QString pic,QString name,QString address,QString intro)
{
    //图片功能暂缺
    label->setText(name+"\n\n"+address+"\n\n"+intro);
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
