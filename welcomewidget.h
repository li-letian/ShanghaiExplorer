#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QCompass>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class WelcomeWidget; }
QT_END_NAMESPACE

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    WelcomeWidget(QWidget *parent = nullptr);
    ~WelcomeWidget();
public slots:
    void updateReading();

private:
    Ui::WelcomeWidget *ui;
    QCompass *compass;
    QCompassReading *compass_reading;
};
#endif // WELCOMEWIDGET_H
