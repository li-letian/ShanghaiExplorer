#ifndef COMPASSVIEW_H
#define COMPASSVIEW_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QLabel>

class CompassView:public QGraphicsView
{
    Q_OBJECT
public:
    explicit CompassView(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    QLabel* label;
};

#endif // COMPASSVIEW_H
