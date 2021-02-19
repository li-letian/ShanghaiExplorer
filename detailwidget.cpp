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
    this->resize(screen.width()*5/6,screen.height()*2/3);
    this->move(screen.width()/12,screen.height()/3);

    setStyleSheet("background-color:rgb(255,255,255,220);color:black;border-radius:20px;border:5px solid green;font:20pt;");

    label=new QLabel(this);
    QFont font("宋体",20,75);
    label->setFont(font);
    label->resize(screen.width()*2/3,screen.height()/2);
    label->move(screen.width()/12,screen.width()/12);
    label->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    connect(this,SIGNAL(clicked()),this,SLOT(hideDetail()));
}

void DetailWidget::updateText(QString name,QString address,QString intro)
{
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
