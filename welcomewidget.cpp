#include "welcomewidget.h"
#include "ui_welcomewidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}

