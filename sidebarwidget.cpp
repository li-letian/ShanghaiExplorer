#include "sidebarwidget.h"

#include <QGuiApplication>
#include <QScreen>
#include <QScroller>
#include <QScrollBar>

SideBarWidget::SideBarWidget(QWidget *parent) :
    QListWidget(parent)
{
}

void SideBarWidget::init(DataLoader* loader)
{
    auto screens = QGuiApplication::screens();
    auto screen=screens.at(0)->availableGeometry();
    setFixedWidth(screen.width()*3/5);
    setFixedHeight(screen.height());
    move(screen.width()*2/5,0);
    setMovement(QListView::Static);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollMode(ScrollMode::ScrollPerPixel);
    setHorizontalScrollMode(ScrollMode::ScrollPerPixel);
    QScroller::grabGesture(this,QScroller::LeftMouseButtonGesture);

    QFont font("宋体",20,75);
    QFont fonti("宋体",20,75);
    auto item = new QListWidgetItem;
    item->setText("设计师：");
    item->setFont(font);
    item->setBackground(QColor(236,200,53));
    this->addItem(item);
    item->setSizeHint(QSize(screen.width()*3/5,screen.height()/6));
    for(auto designer:loader->designer)
    {
        item = new QListWidgetItem;
        item->setText(designer);
        item->setFont(fonti);
        this->addItem(item);
        item->setSizeHint(QSize(screen.width()*3/5,screen.height()/15));
    }

    item = new QListWidgetItem;
    item->setText("保护批次：");
    item->setFont(font);
    item->setBackground(QColor(235,98,66));
    this->addItem(item);
    item->setSizeHint(QSize(screen.width()*3/5,screen.height()/6));
    for(auto batch:loader->batch)
    {
        item = new QListWidgetItem;
        item->setText(batch);
        item->setFont(fonti);
        this->addItem(item);
        item->setSizeHint(QSize(screen.width()*3/5,screen.height()/15));
    }

    item = new QListWidgetItem;
    item->setText("年代：");
    item->setFont(font);
    item->setBackground(QColor(118,170,209));
    this->addItem(item);
    item->setSizeHint(QSize(screen.width()*3/5,screen.height()/6));
    for(auto period:loader->period)
    {
        item = new QListWidgetItem;
        item->setText(period);
        item->setFont(fonti);
        this->addItem(item);
        item->setSizeHint(QSize(screen.width()*3/5,screen.height()/15));
    }

    item = new QListWidgetItem;
    item->setText("建筑风格：");
    item->setFont(font);
    item->setBackground(QColor(34,172,56));
    this->addItem(item);
    item->setSizeHint(QSize(screen.width()*3/5,screen.height()/6));
    for(auto style:loader->style)
    {
        item = new QListWidgetItem;
        item->setText(style);
        item->setFont(fonti);
        this->addItem(item);
        item->setSizeHint(QSize(screen.width()*3/5,screen.height()/15));
    }

    item = new QListWidgetItem;
    item->setText("建筑类型：");
    item->setFont(font);
    item->setBackground(QColor(159,160,160));
    this->addItem(item);
    item->setSizeHint(QSize(screen.width()*3/5,screen.height()/6));
    for(auto type:loader->type)
    {
        item = new QListWidgetItem;
        item->setText(type);
        item->setFont(fonti);
        this->addItem(item);
        item->setSizeHint(QSize(screen.width()*3/5,screen.height()/15));
    }

    isopen=false;
    animation= new QPropertyAnimation(this,"geometry");
    animation->setEasingCurve(QEasingCurve::InOutQuint);
    animation->setDuration(1000);
    this->hide();
}

void SideBarWidget::fade()
{
    auto screens = QGuiApplication::screens();
    auto screen=screens.at(0)->availableGeometry();
    if(isopen)
    {
        isopen=false;
        animation->setStartValue(QRect(screen.width()*2/5,0,screen.width()*3/5,screen.height()));
        animation->setEndValue(QRect(screen.width(),0,screen.width()*3/5,screen.height()));
        animation->start();
    }
    else
    {
        isopen=true;
        this->show();
        animation->setStartValue(QRect(screen.width(),0,screen.width()*3/5,screen.height()));
        animation->setEndValue(QRect(screen.width()*2/5,0,screen.width()*3/5,screen.height()));
        animation->start();
    }
}

SideBarWidget::~SideBarWidget()
{
}
