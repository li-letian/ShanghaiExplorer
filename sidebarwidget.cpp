#include "sidebarwidget.h"

#include <QGuiApplication>
#include <QScreen>
#include <QScroller>

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
    QScroller::grabGesture(this,QScroller::LeftMouseButtonGesture);
    for(auto label:loader->labels)
    {
        auto item = new QListWidgetItem;
        QFont font("宋体",20,75);
        item->setText(label);
        item->setFont(font);
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
