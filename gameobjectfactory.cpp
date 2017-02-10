#include "gameobjectfactory.h"
#include "playertank.h"
#include <QDebug>

using namespace std;


void GameObjectFactory::init(QQmlApplicationEngine *engine)
{
    m_pEngine = engine;
    qDebug() << __FUNCTION__;
    QObject* rootObject = m_pEngine->rootObjects().first();
    m_pField = rootObject->findChild<QQuickItem*>("battleField");
}

shared_ptr<Tank> GameObjectFactory::cretePlayerTank()
{
    QString qmlFile = QStringLiteral("qrc:/PlayerTank.qml");
    QQmlComponent component(m_pEngine, QUrl(qmlFile));
    auto object = qobject_cast<Tank*>(component.create());
    if (object != nullptr) {
        QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);
        object->setParent(m_pField);
        object->setParentItem(m_pField);
    } else
        qDebug() << __FUNCTION__ << "object != nullptr";

    // todo: check memory usage
    shared_ptr<Tank> pPlayerTank(object, [](QObject* ){}); // if deleter is default -> "The program has unexpectedly finished."
    pPlayerTank->setProperty("x", 120);
    pPlayerTank->setProperty("y", 120);

    return pPlayerTank;
}

GameObjectFactory::GameObjectFactory()
{

}
