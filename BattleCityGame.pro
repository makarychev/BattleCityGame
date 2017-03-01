TEMPLATE = app

QT += qml quick
CONFIG += c++11

TARGET = BattleCityGame
INCLUDEPATH += .

# Input
HEADERS += bottank.h \
           brick.h \
           config.h \
           direction.h \
           eagle.h \
           gamecontroller.h \
           gameobject.h \
           gameobjectfactory.h \
           keyhandler.h \
           playertank.h \
           rocket.h \
           tank.h
SOURCES += bottank.cpp \
           gamecontroller.cpp \
           gameobjectfactory.cpp \
           keyhandler.cpp \
           main.cpp \
           playertank.cpp \
           rocket.cpp \
           tank.cpp
RESOURCES += qml.qrc
