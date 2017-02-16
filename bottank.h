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
    std::atomic<bool> m_isPause;
    std::atomic<bool> m_isStop;
    std::future<void> m_activeWorker;
    void activeThread();

signals:
    void signalJustDoIt(bool isFireNeeded);

public slots:
    void justDoIt(bool isFireNeeded);
};

#endif // BOTTANK_H
