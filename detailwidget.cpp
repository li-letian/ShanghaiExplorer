#include "detailwidget.h"
#include "ui_detailwidget.h"
#include "dataloader.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QScreen>
#include <QLabel>
#include <QSize>

DetailWidget::DetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailWidget)
{
    ui->setupUi(this);
    auto screens = QGuiApplication::screens();
    auto screen=screens.at(0)->availableGeometry();
    this->resize(screen.width()*2/3,screen.height()*2/3);
    this->move(screen.width()/6,screen.height()/6);

    label=new QLabel(this);
    label->resize(screen.width()/2,screen.height()/2);
    label->move(screen.width()/12,screen.height()/12);

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
    delete ui;
}
