#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <memory>
#include <future>
#include "rocket.h"

class Tank;
class Brick;
class Rocket;

class GameController : public QObject
{
    Q_OBJECT
public:
    static GameController& get() {
        static GameController self;
        return self;
    }

    void init();
    bool isMoveAllowed(QRect newPos) const;
    bool intersectWorldObj(Rocket* rocket);
    void start();
    void stop();

    void ActiveThread();

signals:

public slots:
    void keyPressed(Qt::Key key);

private:
    GameController() : m_bIsExit(false) {}
    ~GameController() {
        qDebug() << "~GameController()";
        stop();
    }


    std::atomic<bool> m_bIsExit;
    std::future<void> m_backgroundWorker;
    std::shared_ptr<Tank> m_pPlayerTank;
    QList<Brick*> m_bricks;
    std::map<std::size_t, Rocket* > m_rockets;
};

#endif // GAMECONTROLLER_H
