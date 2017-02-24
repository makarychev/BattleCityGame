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
#include <QThread>
#include <exception>

void GameController::init()
{
    m_bricks = GameObjectFactory::get().getBricks();
    m_bricksCache = m_bricks;
    m_eagle = GameObjectFactory::get().getEagle();
    m_gameOver = GameObjectFactory::get().getGameOver();
    m_statistic = GameObjectFactory::get().getStatistic();
    m_leftEnemyCount = Config::get().getEnemyCount();
    m_lifePlayerCount = Config::get().getPlayerLifeCount();
    updateStatistic(m_leftEnemyCount, m_lifePlayerCount);

    m_pPlayerTank = dynamic_cast<PlayerTank *>(GameObjectFactory::get().createTank(GameObjectFactory::Player));
    if (m_pPlayerTank == nullptr)
        throw std::runtime_error("Cannot create player");
    m_pPlayerTank->setPosition(Config::get().getPlayerPosition());
    Rocket *pRocket = GameObjectFactory::get().getRocket(m_pPlayerTank->getDirection(), m_pPlayerTank->getRect());
    pRocket->setTank(m_pPlayerTank);
    pRocket->setVisible(false);
    m_rockets.insert({reinterpret_cast<std::size_t>(m_pPlayerTank), pRocket});

    auto enemyTanksPosition = Config::get().getEnemyPositions();
    foreach (auto position, enemyTanksPosition) {
        auto pBotTank = dynamic_cast<BotTank *>(GameObjectFactory::get().createTank(GameObjectFactory::Enemy));
        if (m_pPlayerTank == nullptr)
            throw std::runtime_error("Cannot create enemy");
        pBotTank->setPosition(position);
        m_enemyTanks.push_back(pBotTank);
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

void GameController::restartGame()
{
    stop();
    start();
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

    case Qt::Key_Escape: // todo: restart
        switch (m_state.load()) {
        case State::Start:
            foreach (auto enemy, m_enemyTanks) {
                enemy->pause(true);
            }
            m_state.store(State::Stop);
            m_gameOver->setProperty("info", "Pause...");
            m_gameOver->setProperty("visible", true);
            break;
        case State::Stop:
            foreach (auto enemy, m_enemyTanks) {
                enemy->pause(false);
            }
            m_state.store(State::Start);
            m_gameOver->setProperty("visible", false);
            break;
        default:
            restartGame();
            break;
        }
    default:
        break;
    }

    if (m_state.load() == State::Start)
        m_pPlayerTank->move(step);
}

bool GameController::isMoveAllowed(const QRect& newPos, const Tank* tank) const
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
            return false;
        }
    }
    if (tank->getType() == Tank::Player) {
        foreach (auto enemy, m_enemyTanks) {
            if(enemy->isActive() && newPos.intersects(enemy->getRect()))
                return false;
        }
    } else {
        if(newPos.intersects(m_pPlayerTank->getRect()))
            return false;
        foreach (auto enemy, m_enemyTanks) {
            if(enemy != tank && newPos.intersects(enemy->getRect()))
                return false;
        }
    }

    return true;
}

void GameController::rocketLaunch(Tank *tank)
{
    Rocket* rocket = m_rockets[reinterpret_cast<std::size_t>(tank)];
    if (rocket->isActive() == false && rocket->getTank()->isActive()) {
        rocket->setDirection(tank->getDirection());
        rocket->setPosition(tank->getRect());
        rocket->setVisible(true);
        rocket->setActive(true);
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
        rocket->blast();
        return true;
    }

    auto pEagle = GameObjectFactory::get().getEagle();
    if (currRect.intersects(pEagle->getRect())) {
        rocket->blast();
        pEagle->setVisible(false);
        m_state.store(State::GameOver);
        m_gameOver->setProperty("info", "Game over");
        m_gameOver->setProperty("visible", true);
        return true;
    }

    if (rocket->getTank()->getType() == Tank::Player) {
        foreach (auto enemy, m_enemyTanks) {
            if (enemy->isActive() && currRect.intersects(enemy->getRect())){
                rocket->blast();
                enemy->killed();

                std::unique_lock<std::mutex> m_lock(m_mutex);
                if (m_leftEnemyCount - m_enemyTanks.length() > 0) {
                    enemy->restart();
                }
                m_leftEnemyCount--;
                if (m_leftEnemyCount == 0) {
                    m_state.store(State::Win);
                    m_gameOver->setProperty("info", "You won!");
                    m_gameOver->setProperty("visible", true);
                }
                updateStatistic(m_leftEnemyCount, m_lifePlayerCount);

                return true;
            }
        }
    } else if (currRect.intersects(m_pPlayerTank->getRect())) {
        rocket->setActive(false);
        rocket->setVisible(false);
        m_pPlayerTank->setVisible(false);
        std::unique_lock<std::mutex> m_lock(m_mutex);
        m_lifePlayerCount--;
        if (m_lifePlayerCount == 0) {
            m_state.store(State::GameOver);
            m_gameOver->setProperty("info", "Game over");
            m_gameOver->setProperty("visible", true);
        } else if (m_lifePlayerCount > 0) {
            m_pPlayerTank->restart(Config::get().getPlayerPosition());
        }
        updateStatistic(m_leftEnemyCount, m_lifePlayerCount);
        return true;
    }

    foreach (auto brick, m_bricks) {
        if (currRect.intersects(brick->getRect())){
            brick->setVisible(false);
            rocket->blast();
            m_bricks.removeOne(brick);
            return true;
        }
    }

    return false;
}

QPoint GameController::findEnemyRespawn(const BotTank &curEnemy)
{
    auto enemyPositions = Config::get().getEnemyPositions();
    foreach (auto startPoint, enemyPositions) {
        QRect startRect(startPoint, curEnemy.getSize());
        if (!startRect.intersects(m_pPlayerTank->getRect())) {
            auto tankCount = m_enemyTanks.length() - 1; // -1 - for curEnemy
            foreach (auto enemy, m_enemyTanks) {
                if (&curEnemy != enemy && !startRect.intersects(enemy->getRect())) {
                    tankCount--;
                }
            }
            if (tankCount == 0)
                return startPoint;
        }
    }

    throw std::runtime_error("no empty position");
    return QPoint();
}

void GameController::start()
{
    m_leftEnemyCount = Config::get().getEnemyCount();
    m_lifePlayerCount = Config::get().getPlayerLifeCount();
    updateStatistic(m_leftEnemyCount, m_lifePlayerCount);

    foreach (auto brick, m_bricksCache) {
        brick->setVisible(true);
    }

    m_bricks = m_bricksCache;
    m_eagle->setVisible(true);
    m_pPlayerTank->restart(Config::get().getPlayerPosition());

    m_bIsExit.store(false);
    m_state.store(State::Start);
    m_backgroundWorker = std::async(std::launch::async, &GameController::rocketsThread, this);

    auto enemyTanksPosition = Config::get().getEnemyPositions();
    auto itPos = std::begin(enemyTanksPosition);
    auto itBot = std::begin(m_enemyTanks);
    while (itPos != std::end(enemyTanksPosition)) {
        (*itBot)->setPosition(*itPos);
        ++itBot;
        ++itPos;
    }

    foreach (auto botTank, m_enemyTanks) {
        botTank->start();
    }

    m_state.store(State::Start);
    m_gameOver->setProperty("visible", false);
}

void GameController::stop()
{
    m_bIsExit.store(true);

    if (m_backgroundWorker.valid()){
        if (m_backgroundWorker.wait_for(std::chrono::seconds(2)) == std::future_status::ready) // in case resolve freezing if smth bad happens
            m_backgroundWorker.get();
    }
    foreach (auto botTank, m_enemyTanks) {
        botTank->stop();
    }
}

void GameController::rocketsThread()
{
    int step = 3;
    while (!m_bIsExit){
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        auto curState = m_state.load();
        if (curState == State::Start || curState == State::GameOver) {
            foreach (auto item, m_rockets) {
                if (item.second->isActive()) {
                        item.second->moveTarget(step);
                }
            }
        }
    }
}
