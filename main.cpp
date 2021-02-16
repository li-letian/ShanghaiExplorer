#include "welcomewidget.h"
#include "dataloader.h"

#include "homepagewidget.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QElapsedTimer>
#include <QDebug>
#include <QScreen>
#include <QLabel>
#include <QTextStream>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //创建欢迎页背景
    auto screens = QGuiApplication::screens();
    auto screen=screens.at(0)->availableGeometry();
    QPixmap pixmap(":/loading.png");
    auto background=pixmap.scaled(screen.width(),screen.height(),Qt::KeepAspectRatioByExpanding);
    QSplashScreen splash(background);
    splash.show();

    //加载数据
    DataLoader dataloader;
    dataloader.load();

    //欢迎页延迟
    int delayTime = 3;
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed() < (delayTime * 1000))
    {
         a.processEvents();
    }

    //主界面
    HomePageWidget w;

    //debug标签
    QString str;
    str=dataloader.name(3)+"\n";
    for(auto s: dataloader.labels)
    {
        str+=s+"\n";
    }
    QLabel label(&w);
    label.setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label.setText(str);
    label.setAlignment(Qt::AlignBottom | Qt::AlignRight);


    w.show();
    splash.finish(&w);
    return a.exec();
}
