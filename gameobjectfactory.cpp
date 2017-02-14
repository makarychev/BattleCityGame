#include <QDebug>
#include "gameobjectfactory.h"
#include "playertank.h"
#include "brick.h"
#include "rocket.h"

using namespace std;


void GameObjectFactory::init(QQmlApplicationEngine *engine)
{
    m_pEngine = engine;
    qDebug() << __FUNCTION__;
    m_rootObject = m_pEngine->rootObjects().first();
    m_pBattleField = m_rootObject->findChild<QQuickItem*>("battleField");
}

shared_ptr<Tank> GameObjectFactory::cretePlayerTank()
{
    QString qmlFile = QStringLiteral("qrc:/PlayerTank.qml");
    QQmlComponent component(m_pEngine, QUrl(qmlFile));
    auto object = qobject_cast<Tank*>(component.create());
    if (object != nullptr) {
        QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);
        object->setParent(m_pBattleField);
        object->setParentItem(m_pBattleField);
    } else
        qDebug() << __FUNCTION__ << "object != nullptr";

    // todo: check memory usage
    shared_ptr<Tank> pPlayerTank(object, [](QObject* ){}); // if deleter is default -> "The program has unexpectedly finished."
    pPlayerTank->setProperty("x", 0); // todo: should be in another place
    pPlayerTank->setProperty("y", 0);

    return pPlayerTank;
}

QList<Brick *> GameObjectFactory::getBricks() const
{
    QObject* rootObject = m_pEngine->rootObjects().first();
    QList<Brick*> briks = rootObject->findChildren<Brick*>("brick");

    return briks;
}

QQuickItem *GameObjectFactory::getBattleField() const
{
    return m_pBattleField;
}

// todo: create object pool and reuse it
Rocket *GameObjectFactory::getRocket(Direction direction, QRect startPosition) const
{
    QString qmlFile = QStringLiteral("qrc:/Rocket.qml");
    QQmlComponent component(m_pEngine, QUrl(qmlFile));
    Rocket* object = qobject_cast<Rocket*>(component.create());
    if (object != nullptr) {
        QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);
        object->setParentItem(m_pBattleField);
        object->setParent(m_pBattleField);
        object->setDirection(direction);
        int x = startPosition.x(), y = startPosition.y();
        switch (direction) {
        case Direction::UP:
            x = startPosition.x() + startPosition.width()/2;
            break;
        case Direction::DOWN:
            x = startPosition.x() + startPosition.width()/2;
            y = startPosition.y() + startPosition.height();
            break;
        case Direction::RIGHT:
            x = startPosition.x() + startPosition.width();
            y = startPosition.y() + startPosition.height()/2;
            break;
        case Direction::LEFT:
            y = startPosition.y() + startPosition.height()/2;
            break;
        default:
            break;
        }
        object->setX(x);
        object->setY(y);
    }
    qDebug() << "Rocket creation: " << object;
    return object;
}

GameObjectFactory::GameObjectFactory()
{

}
