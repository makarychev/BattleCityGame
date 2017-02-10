#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <memory>


class Tank;

class GameObjectFactory
{
public:
    static GameObjectFactory& get(){
        static GameObjectFactory self;
        return self;
    }

    void init(QQmlApplicationEngine* engine);
    std::shared_ptr<Tank> cretePlayerTank();

private:
    GameObjectFactory();

    QQmlApplicationEngine* m_pEngine = nullptr;
    QQuickItem* m_pField = nullptr;
};

#endif // GAMEOBJECTFACTORY_H
