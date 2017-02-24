#include "bottank.h"
#include <cstdlib>
#include "QDebug"
#include "QThread"
#include "gamecontroller.h"

using namespace std;

BotTank::BotTank() : Tank(Tank::Type::Enemy), m_isPause(false), m_isStop(false), m_isRestart(false)
{
    connect(this, SIGNAL(signalRandomActionSequence(bool)), SLOT(randomActionSequence(bool)));
    connect(this, SIGNAL(signalRestart()), SLOT(slRestart()));
}

BotTank::~BotTank()
{
    stop();
}

void BotTank::start()
{
    m_isActive.store(true);
    m_isStop.store(false);
    setVisible(true);
    m_activeWorker = async(std::launch::async, &BotTank::activeThread, this);
}

void BotTank::pause(bool status)
{
    m_isPause.store(status);
}

void BotTank::killed()
{
    m_isActive.store(false);
    setVisible(false);
}

void BotTank::stop()
{
    m_isActive.store(false);
    m_isStop.store(true);
    if (m_activeWorker.valid()){
        if (m_activeWorker.wait_for(std::chrono::seconds(2)) == std::future_status::ready) {// in case resolve freezing if smth bad happens
            m_activeWorker.get();
        }
    }
}

void BotTank::restart(chrono::milliseconds timeout)
{
    m_isRestart.store(true);
    m_restartTimeout = timeout;
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

    while (m_isStop.load() == false){
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (m_isPause.load() == false) {
            emit signalRandomActionSequence(isFireNeeded());
        }
        if (m_isRestart.load() == true) {
            std::this_thread::sleep_for(m_restartTimeout);
            emit signalRestart();
        }
    }
}

void BotTank::randomActionSequence(bool isFireNeeded)
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
        rotate(dir);
    }
    if (isFireNeeded) {
        fire();
    }
}

void BotTank::slRestart()
{
    try {
        auto point = GameController::get().findEnemyRespawn(*this);
        setPosition(point);
    } catch (...) {
        qDebug() << "NO EMPTY PLACE!!!";
        return; // no empty place
    }

    setVisible(true);
    m_isActive.store(true);
    m_isPause.store(false);
    m_isRestart.store(false);
}



