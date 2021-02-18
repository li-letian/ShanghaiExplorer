#include "floatpan.h"
#include "ui_floatpan.h"

FloatPan::FloatPan(QWidget *parent,QString text) :
    QWidget(parent),
    ui(new Ui::floatpan)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
    QFont font;
    font.setPixelSize(20);
    font.setBold(true);
    ui->textEdit->setFont(font);
}

FloatPan::~FloatPan()
{
    delete ui;
}

void FloatPan::setCustomText(QString text)
{
    ui->textEdit->setText(text);
}
