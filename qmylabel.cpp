#include "qmylabel.h"

QMyLabel::QMyLabel(QWidget *parent)
{
    this->setMouseTracking(true);
}

void QMyLabel::enterEvent(QEvent * event)
{
    emit show();
}

void QMyLabel::leaveEvent(QEvent * event)
{
    emit hide();
}
