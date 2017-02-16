#include "bottank.h"
#include <cstdlib>
#include "QDebug"
#include "QThread"

using namespace std;

BotTank::BotTank() : Tank(Tank::Type::Enemy), m_isPause(false)
{
    connect(this, SIGNAL(signalJustDoIt(bool)), SLOT(justDoIt(bool)));
}

BotTank::~BotTank()
{
    stop();
}

void BotTank::start()
{
    m_activeWorker = async(std::launch::async, &BotTank::activeThread, this);
}

void BotTank::pause(bool status)
{
    m_isPause.store(status);
}

void BotTank::stop()
{
    m_isStop.store(true);
    if (m_activeWorker.valid()){
        if (m_activeWorker.wait_for(std::chrono::seconds(2)) == std::future_status::ready) {// in case resolve freezing if smth bad happens
            m_activeWorker.get();
        }
    }
}

void BotTank::activeThread()
{
    srand (time(NULL));

    uint cycle = 0;
    auto isFireNeeded = [&cycle](){
        if (cycle % 30 == 0) {
            cycle = 0;
            return true;
        } else {
            cycle++;
            return false;
        }
    };

    while (!m_isStop){
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (m_isPause.load() == false) {
            emit signalJustDoIt(isFireNeeded());
        }
    }
}

void BotTank::justDoIt(bool isFireNeeded)
{
    auto getRandDirection = [] () {
        int random_variable = std::rand();
        Direction dir = static_cast<Direction>(random_variable % DIRECTION_NUM);
        return dir;
    };
    auto isRotationNeed = [] () {
        int random_variable = std::rand();
        return static_cast<bool>(random_variable % 4) ;
    };

    move(getDirection());
    if (isRotationNeed()) {
        auto dir = getRandDirection();
//        qDebug() << QThread::currentThreadId() << " direction = " << dir;
        rotate(dir);
    }
    if (isFireNeeded) {
//        qDebug() << QThread::currentThreadId() << " BotTank::activeThread() - fire";
        fire();
    }
}



