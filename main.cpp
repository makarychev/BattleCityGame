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

    qmlRegisterType<PlayerTank>("Game.PlayerTank", 1, 0, "PlayerTank");
    qmlRegisterType<KeyHandler>("Game.KeyHandler", 1, 0, "KeyHandlerCpp");
    qmlRegisterType<Brick>("Game.Brick", 1, 0, "BrickCpp");
    qmlRegisterType<Rocket>("Game.Rocket", 1, 0, "RocketCpp");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    qDebug() << "start object creation";

    GameObjectFactory::get().init(&engine);
    GameController::get().init(); // engine.rootObjects().first()

    GameController::get().start();

    return app.exec();
}
