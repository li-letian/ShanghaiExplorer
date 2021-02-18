#ifndef QMYLABEL_H
#define QMYLABEL_H

#include <QObject>
#include <QLabel>

class QMyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QMyLabel(QWidget *parent = nullptr);

signals:
    void show();
    void hide();

public slots:

private:
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);
};

#endif // QMYLABEL_H
