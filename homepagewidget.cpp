#include "homepagewidget.h"
#include "ui_homepagewidget.h"

HomePageWidget::HomePageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePageWidget)
{
    ui->setupUi(this);
}

HomePageWidget::~HomePageWidget()
{
    delete ui;
}
