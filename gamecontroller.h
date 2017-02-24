#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <memory>
#include <future>

class Tank;
class PlayerTank;
class BotTank;
class Brick;
class Rocket;
class Eagle;

class GameController : public QObject
{
    Q_OBJECT
public:
    static GameController& get() {
        static GameController self;
        return self;
    }

    void init();
    bool isMoveAllowed(const QRect& newPos, const Tank* tank) const;
    void rocketLaunch(Tank* tank);
    bool intersectWorldObj(Rocket* rocket);
    QPoint findEnemyRespawn(const BotTank& enemy);
    void start();
    void stop();

private:
    void rocketsThread();
    void updateStatistic(int left, int lives);
    void restartGame();

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

    PlayerTank* m_pPlayerTank;
    QList<Brick *> m_bricks;
    QList<Brick *> m_bricksCache;
    QList<BotTank *> m_enemyTanks;
    std::map<std::size_t, Rocket* > m_rockets;
    Eagle* m_eagle = nullptr;
    QObject* m_gameOver = nullptr;
    QObject* m_statistic = nullptr;
    int m_leftEnemyCount = 0;
    int m_lifePlayerCount = 0;
    std::mutex m_mutex;
};

#endif // GAMECONTROLLER_H
