#ifndef DETAILWIDGET_H
#define DETAILWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QObject>

#include "dataloader.h"

namespace Ui {
class DetailWidget;
}

class DetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DetailWidget(QWidget *parent = nullptr);
    ~DetailWidget();

    void updateText(QString name,QString address,QString intro);

signals:
    void clicked();

public slots:
    void hideDetail();

protected:
    virtual void mouseReleaseEvent(QMouseEvent * ev);

private:
    Ui::DetailWidget *ui;
    QLabel* label;
};

#endif // DETAILWIDGET_H
