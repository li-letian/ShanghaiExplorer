#include "sidebar.h"
#include "ui_sidebar.h"
#include <QPropertyAnimation>

sideBar::sideBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sideBar)
{
    ui->setupUi(this);

}

sideBar::~sideBar()
{
    delete ui;
}
