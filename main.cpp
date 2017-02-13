#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include "playertank.h"
#include "keyhandler.h"
#include "gameobjectfactory.h"
#include "gamecontroller.h"
#include "brick.h"

int main(int argc, char *argv[])
{
    qDebug() << __FUNCTION__ << "start ";

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<PlayerTank>("com.game.playerTank", 1, 0, "PlayerTank");
    qmlRegisterType<KeyHandler>("com.game.keyhandler", 1, 0, "KeyHandlerCpp");
    qmlRegisterType<Brick>("com.game.brick", 1, 0, "BrickCpp");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    qDebug() << "start object creation";

    GameObjectFactory::get().init(&engine);
    GameController::get().init(); // engine.rootObjects().first()

    return app.exec();
}
