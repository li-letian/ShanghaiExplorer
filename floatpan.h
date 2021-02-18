#ifndef FLOATPAN_H
#define FLOATPAN_H

#include <QWidget>

namespace Ui {
class floatpan;
}

class FloatPan : public QWidget
{
    Q_OBJECT

public:
    explicit FloatPan(QWidget *parent = 0,QString text = "default");
    ~FloatPan();

     void setCustomText(QString text);

private:

    Ui::floatpan *ui;
};
#endif // FLOATPAN_H
