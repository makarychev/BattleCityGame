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
    void restart(std::chrono::milliseconds timeout = std::chrono::milliseconds(4000));
    void killed();

private:
    std::atomic<bool> m_isPause;
    std::atomic<bool> m_isStop;
    std::atomic<bool> m_isRestart;
    std::future<void> m_activeWorker;
    std::chrono::milliseconds m_restartTimeout;
    void activeThread();

signals:
    void signalRandomActionSequence(bool isFireNeeded);
    void signalRestart();

public slots:
    void randomActionSequence(bool isFireNeeded);
    void slRestart();
};

#endif // BOTTANK_H
