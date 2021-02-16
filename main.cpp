#include "welcomewidget.h"
#include "homepagewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomePageWidget w;
    w.show();
    return a.exec();
}
