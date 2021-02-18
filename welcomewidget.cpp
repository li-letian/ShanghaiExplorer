#include "welcomewidget.h"
#include "ui_welcomewidget.h"

#include <QTimer>

WelcomeWidget::WelcomeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

    //debug
    auto label = new QLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setAlignment(Qt::AlignBottom | Qt::AlignRight);

    compass = new QCompass(this);
    connect(compass, SIGNAL(readingChanged()), this, SLOT(updateReading()));
    compass->setDataRate(1);
    compass->start();

    if (compass->isBusy())
    {
        // Label Debug
        label->setText(label->text()+"\n"+"QCompass is busy...");
    }
    if(compass->isConnectedToBackend())
    {
        label->setText(label->text()+"\n"+"QCompass is connected to backend...");
    }
    if(compass->isActive())
    {
        label->setText(label->text()+"\n"+"QCompass isActive...");
    }
    compass_reading=compass->reading();
    }

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}

void WelcomeWidget::updateReading()
{
    QString text;
    auto label = new QLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    compass_reading = compass->reading();
    if(compass_reading != 0)
    {
        label->setText(label->text()+"\n"+"azimuth:"+QString::number(compass_reading->azimuth()));
    }
    else
    {
        text = "Compass: UNAVAILABLE";
        label->setText(label->text()+"\n"+text);
    }
    repaint();
}
