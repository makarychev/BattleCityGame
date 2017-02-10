#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include "playertank.h"
#include "keyhandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<PlayerTank>("com.game.playerTank", 1, 0, "PlayerTank");
    qmlRegisterType<KeyHandler>("com.game.keyhandler", 1, 0, "KeyHandlerCpp");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject* rootObject = engine.rootObjects().first();
    QQuickItem* field = rootObject->findChild<QQuickItem*>("battleField");

    QScopedPointer<PlayerTank> pPlayerTank(new PlayerTank);
    QString qmlFile = QStringLiteral("qrc:/PlayerTank.qml");
    QQmlComponent component(&engine, QUrl(qmlFile));
    auto object = qobject_cast<PlayerTank*>(component.create());
    if (object != nullptr) {
        QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);
        object->setParent(field);
        object->setParentItem(field);
    }

    pPlayerTank->setProperty("x", 120);
    pPlayerTank->setProperty("y", 120);


    return app.exec();
}
