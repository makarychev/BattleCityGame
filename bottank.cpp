#include "bottank.h"
#include <cstdlib>

using namespace std;

BotTank::BotTank() : m_isPause(false), m_isStop(false)
{
    connect(this, SIGNAL(signalMove()), SLOT(moveTarget()));
    connect(this, SIGNAL(signalRotate(Direction)), SLOT(rotateTarget(Direction)));
}

BotTank::~BotTank()
{
    stop();
}

void BotTank::start()
{
    m_activeWorker = async(std::launch::async, &BotTank::ActiveThread, this);
}

void BotTank::pause(bool status)
{
    m_isPause.store(status);
}

void BotTank::stop()
{
    qDebug() << "BotTank::stop()";
    m_isStop.store(true);
    if (m_activeWorker.valid()){
        qDebug() << "BotTank::stop() | m_activeWorker.valid()";
        if (m_activeWorker.wait_for(std::chrono::seconds(2)) == std::future_status::ready) {// in case resolve freezing if smth bad happens
            m_activeWorker.get();
        }
    }
}

void BotTank::ActiveThread()
{
    srand (time(NULL));
    auto getDirection = [] () {
        int random_variable = std::rand();
        Direction dir = static_cast<Direction>(random_variable % DIRECTION_RAND_NUM);
        return dir;
    };
    auto isRotationNeed = [] () {
        int random_variable = std::rand();
        return static_cast<bool>(random_variable % 2);
    };

    while (!m_isStop){
        this_thread::sleep_for(std::chrono::milliseconds(100));
        if (m_isPause.load() == false) {
            emit signalMove();
            if (isRotationNeed())
                emit rotateTarget(getDirection());
        }
    }
}

void BotTank::moveTarget()
{
    move(getDirection());
}

void BotTank::rotateTarget(Direction direction)
{
    rotate(direction);
}


