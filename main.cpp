#include "welcomewidget.h"
#include "dataloader.h"

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
#include "compassview.h"

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

    // Mark: 创建场景
    auto compass_scene = new QGraphicsScene;

    // Mark: 创建视图并与场景绑定
    CompassView compass_view;
    compass_view.resize(screen.width(),screen.height());
    compass_view.setScene(compass_scene);

    // Mark: 初始化视图
    compass_scene->setSceneRect(-screen.width()/2,-screen.height()/2,screen.width(),screen.height());
    compass_view.Init();

    //debug标签
//    QString str;
//    str=dataloader.name(3)+"\n";
//    for(auto s: dataloader.labels)
//    {
//        str+=s+"\n";
//    }
//    QLabel label(&compass_view);
//    label.setFrameStyle(QFrame::Panel | QFrame::Sunken);
//    label.setText(str);
//    label.setAlignment(Qt::AlignBottom | Qt::AlignRight);


    compass_view.show();
    splash.finish(&compass_view);
    return a.exec();
}
