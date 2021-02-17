#ifndef COMPASSVIEW_H
#define COMPASSVIEW_H

#include <QGraphicsItem>
#include <QGraphicsView>

class CompassView:public QGraphicsView
{
    Q_OBJECT
public:
    explicit CompassView(QWidget *parent = 0);
    void Init();
protected:
    void mousePressEvent(QMouseEvent *event);
private:
};

#endif // COMPASSVIEW_H
