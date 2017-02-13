#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <memory>


class Tank;
class Brick;
class BattleField;

class GameObjectFactory
{
public:
    static GameObjectFactory& get(){
        static GameObjectFactory self;
        return self;
    }

    void init(QQmlApplicationEngine* engine);
    std::shared_ptr<Tank> cretePlayerTank();
    QList<Brick *> getBricks() const;
    QQuickItem *getBattleField() const;

private:
    GameObjectFactory();

    QQmlApplicationEngine* m_pEngine = nullptr;
    QQuickItem* m_pBattleField = nullptr;
    QObject* m_rootObject = nullptr;
};

#endif // GAMEOBJECTFACTORY_H
