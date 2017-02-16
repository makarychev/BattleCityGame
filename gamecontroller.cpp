#include "gamecontroller.h"
#include "gameobjectfactory.h"
#include "playertank.h"
#include <QDebug>
#include <QPoint>
#include "brick.h"
#include "rocket.h"
#include "eagle.h"
#include "bottank.h"
#include "config.h"
#include "QThread"

void GameController::init()
{
    m_bricks = GameObjectFactory::get().getBricks();
    m_eagle = GameObjectFactory::get().getEagle();
    m_gameOver = GameObjectFactory::get().getGameOver();
    m_statistic = GameObjectFactory::get().getStatistic();
    m_leftEnemyCount = Config::get().getEnemyCount();
    m_lifePlayerCount = Config::get().getPlayerLifeCount();
    updateStatistic(m_leftEnemyCount, m_lifePlayerCount);

    m_pPlayerTank = GameObjectFactory::get().createTank(GameObjectFactory::Player);
    m_pPlayerTank->setPosition(Config::get().getPlayerPosition());
    Rocket *pRocket = GameObjectFactory::get().getRocket(m_pPlayerTank->getDirection(), m_pPlayerTank->getRect());
    pRocket->setTank(m_pPlayerTank);
    pRocket->setVisible(false);
    m_rockets.insert({reinterpret_cast<std::size_t>(m_pPlayerTank), pRocket});

    auto enemyTanksPosition = Config::get().getEnemyPositions();
    foreach (auto position, enemyTanksPosition) {
        auto pBotTank = dynamic_cast<BotTank *>(GameObjectFactory::get().createTank(GameObjectFactory::Enemy));
        pBotTank->setPosition(position);
        m_botTanks.push_back(pBotTank);
        Rocket *pRocket = GameObjectFactory::get().getRocket(pBotTank->getDirection(), pBotTank->getRect());
        pRocket->setTank(pBotTank);
        pRocket->setVisible(false);
        m_rockets.insert({reinterpret_cast<std::size_t>(pBotTank), pRocket});
    }
}

void GameController::updateStatistic(int left, int lives)
{
    QString sInfo = "Total enemies left: " + QString::number(left);
    sInfo += "\tPlayer lives left: " + QString::number(lives);

    m_statistic->setProperty("information", sInfo);
}


void GameController::keyPressed(Qt::Key key)
{
    Direction step = Direction::NONE;
    switch (key) {
    case Qt::Key_Up:
        step = Direction::UP;
        break;
    case Qt::Key_Down:
        step = Direction::DOWN;
        break;
    case Qt::Key_Left:
        step = Direction::LEFT;
        break;
    case Qt::Key_Right:
        step = Direction::RIGHT;
        break;
    case Qt::Key_Space:
        m_pPlayerTank->fire();
        return;

    case Qt::Key_Escape:
        switch (m_state.load()) {
        case State::Start:
            m_state.store(State::Stop);
            break;
        case State::Stop:
            m_state.store(State::Start);
            break;
        default:
            break;
        }
    default:
        break;
    }

    if (m_state.load() == State::Start)
        m_pPlayerTank->move(step);
}

bool GameController::isMoveAllowed(QRect newPos) const
{
    auto battleField = GameObjectFactory::get().getBattleField();
    if (newPos.x() < 0
            || newPos.y() <0
            || newPos.x() > battleField->width() - newPos.width()
            || newPos.y() > battleField->height() - newPos.height())
        return false;

    auto pEagle = GameObjectFactory::get().getEagle();
    if (newPos.intersects(pEagle->getRect())) {
        return false;
    }

    foreach (auto brick, m_bricks) {
        if (newPos.intersects(brick->getRect())){
//            qDebug() << "newPos: " << newPos << " | brick: " << brick->getRect();
            return false;
        }
    }
    return true;
}

void GameController::rocketLaunch(Tank *tank)
{
    Rocket* rocket = m_rockets[reinterpret_cast<std::size_t>(tank)];
//    qDebug() << rocket;
    if (rocket->isVisible() == false) {
//        qDebug() << "rocket---->activate!!!" ;
        rocket->setDirection(tank->getDirection());
        rocket->setPosition(tank->getRect());
        rocket->setVisible(true);
//        qDebug() << rocket << " | Direction: " << rocket->getDirection();
    }
}

bool GameController::intersectWorldObj(Rocket *rocket)
{
    auto currRect = rocket->getRect();
    auto battleField = GameObjectFactory::get().getBattleField();
    if (currRect.x() < 0
            || currRect.y() <0
            || currRect.x() > battleField->width() - currRect.width()
            || currRect.y() > battleField->height() - currRect.height()) {
//        m_rockets.erase(reinterpret_cast<std::size_t>(rocket->getTank())); // todo: add ThreadSafety
//        qDebug() << QThread::currentThreadId() << " rocket INTERSECTS!!!1";
        rocket->setVisible(false);
        return true;
    }

    auto pEagle = GameObjectFactory::get().getEagle();
    if (currRect.intersects(pEagle->getRect())) {
//        m_rockets.erase(reinterpret_cast<std::size_t>(rocket->getTank())); // todo: add ThreadSafety
//        qDebug() << QThread::currentThreadId() << " rocket INTERSECTS!!!2";
        rocket->setVisible(false);
        pEagle->setVisible(false);
        m_state.store(State::GameOver);
        m_gameOver->setProperty("visible", true);
        // todo: set game state END
        return true;
    }

    foreach (auto brick, m_bricks) {
        if (currRect.intersects(brick->getRect())){
//            qDebug() << QThread::currentThreadId() << " rocket INTERSECTS!!!3";
//            qDebug() << "Rocket hit brick: ";
            brick->setVisible(false);
            rocket->setVisible(false);
//            m_rockets.erase(reinterpret_cast<std::size_t>(rocket->getTank()));
            m_bricks.removeOne(brick); // todo: think about big O notation perfomance
            return true;
        }
    }

    return false;
}

void GameController::start()
{
    using namespace std;
    m_bIsExit.store(false);
    m_state.store(State::Start);
    m_backgroundWorker = async(std::launch::async, &GameController::ActiveThread, this);
    foreach (auto botTank, m_botTanks) {
        botTank->start();
    }
}

void GameController::stop()
{
    m_bIsExit.store(true);

    if (m_backgroundWorker.valid()){
        if (m_backgroundWorker.wait_for(std::chrono::seconds(2)) == std::future_status::ready) // in case resolve freezing if smth bad happens
            m_backgroundWorker.get();
    }
    foreach (auto botTank, m_botTanks) {
        botTank->stop();
    }
}

void GameController::ActiveThread()
{
    int step = 3;
    while (!m_bIsExit){
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (m_state.load() == State::Start) {
            foreach (auto item, m_rockets) {
                if (item.second->isVisible())
                    item.second->moveTarget(step);
            }
        }
    }
}
