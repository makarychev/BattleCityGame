#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <memory>
#include <direction.h>
#include "rocket.h"

class Tank;
class Brick;
class Rocket;
class BattleField;
class Eagle;

class GameObjectFactory
{
public:
    enum TankType {
        Player,
        Enemy
    };
    static GameObjectFactory& get(){
        static GameObjectFactory self;
        return self;
    }

    void init(QQmlApplicationEngine* engine);
    Tank* createTank(TankType type) const;
    QList<Brick *> getBricks() const;
    QQuickItem *getBattleField() const;
    Rocket *getRocket(Direction direction, QRect startPosition) const;
    Eagle *getEagle() const;
    QObject *getGameOver() const;
    QObject *getStatistic() const;

private:
    GameObjectFactory() = default;

    QQmlApplicationEngine* m_pEngine = nullptr;
    QQuickItem* m_pBattleField = nullptr;
    QObject* m_rootObject = nullptr;
};

#endif // GAMEOBJECTFACTORY_H
