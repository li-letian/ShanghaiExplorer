#include "homepagewidget.h"
#include "ui_homepagewidget.h"
#include <QVBoxLayout>

HomePageWidget::HomePageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePageWidget)
{

    ui->setupUi(this);

    // Mark: 创建场景
    auto compass_scene = new QGraphicsScene;

    // Mark: 创建视图并与场景绑定
    compass_view_ = new CompassView(this);
    compass_view_->setScene(compass_scene);

    // Mark: 管理布局
    auto page_layout = new QVBoxLayout;
    page_layout->addWidget(compass_view_);

    this->setLayout(page_layout);

    // Mark: 初始化视图

    compass_view_->Init();

}

HomePageWidget::~HomePageWidget()
{
    delete ui;
}
