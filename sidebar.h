#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class sideBar;
}

class sideBar : public QWidget
{
    Q_OBJECT
    //Q_PROPERTY(int alpha READ alpha WRITE setAlpha)
public:
    explicit sideBar(QWidget *parent = nullptr);
    ~sideBar();

    bool side_widget_flag;

private:
    Ui::sideBar *ui;
};

#endif // SIDEBAR_H
