#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPropertyAnimation>

#include "dataloader.h"

namespace Ui {
class SideBarWidget;
}

class SideBarWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit SideBarWidget(QWidget *parent = nullptr);
    ~SideBarWidget();

    void init(DataLoader*);
public slots:
    void fade();
private:
    bool isopen;
    QPropertyAnimation* animation;
};

#endif // SIDEBARWIDGET_H
