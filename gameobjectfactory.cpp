#include <QDebug>
#include "gameobjectfactory.h"
#include "playertank.h"
#include "brick.h"

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

GameObjectFactory::GameObjectFactory()
{

}
