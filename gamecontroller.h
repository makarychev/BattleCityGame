#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <memory>
#include <future>

class Tank;
class Brick;
class Rocket;
class Eagle;
class BotTank;

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
    void rocketLaunch(Tank* tank);
    bool intersectWorldObj(Rocket* rocket);
    void start();
    void stop();

    void ActiveThread();

signals:

public slots:
    void keyPressed(Qt::Key key);

private:
    GameController() : m_bIsExit(false),  m_state(Stop) {}
    ~GameController() {
        stop();
    }
    enum State {
        Stop,
        Start,
        GameOver,
        Win
    };

    std::atomic<bool> m_bIsExit;
    std::atomic<bool> m_bIsStopped;
    std::atomic<State> m_state;
    std::future<void> m_backgroundWorker;
    Tank* m_pPlayerTank;
    QList<Brick *> m_bricks;
    QList<BotTank *> m_botTanks;
    std::map<std::size_t, Rocket* > m_rockets;
    Eagle* m_eagle = nullptr;
    QObject* m_gameOver = nullptr;
};

#endif // GAMECONTROLLER_H
