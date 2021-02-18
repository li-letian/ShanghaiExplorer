lessThan(QT_MAJOR_VERSION, 5): error(This project requires Qt 5 or later)

QT += core gui widgets sensors positioning

CONFIG += c++11

TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dataloader.cpp \
    compassview.cpp \
    main.cpp \
    triangleitem.cpp \
    welcomewidget.cpp

HEADERS += \
    dataloader.h \
    compassview.h \
    triangleitem.h \
    welcomewidget.h

FORMS += \
    welcomewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
