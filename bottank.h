#ifndef BOTTANK_H
#define BOTTANK_H
#include "tank.h"
#include <future>

class BotTank : public Tank
{
    Q_OBJECT
public:
    explicit BotTank();
    ~BotTank();

    void start();
    void pause(bool status);
    void stop();
private:
    std::future<void> m_activeWorker;
    std::atomic<bool> m_isPause;
    std::atomic<bool> m_isStop;
    void ActiveThread();

signals:
    void signalMove();
    void signalRotate(Direction direction);

public slots:
    void moveTarget();
    void rotateTarget(Direction direction);
};

#endif // BOTTANK_H
