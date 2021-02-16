#include "welcomewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeWidget w;
    w.show();
    return a.exec();
}
