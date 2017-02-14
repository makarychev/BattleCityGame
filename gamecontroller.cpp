#include "gamecontroller.h"
#include "gameobjectfactory.h"
#include "playertank.h"
#include <QDebug>
#include <QPoint>
#include "brick.h"
#include "rocket.h"

void GameController::init()
{
    m_pPlayerTank = GameObjectFactory::get().cretePlayerTank();
    m_bricks = GameObjectFactory::get().getBricks();
}

void GameController::keyPressed(Qt::Key key)
{
    Direction step = Direction::NONE;
    Rocket* pRocket = nullptr;
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
        qDebug() << "Up-Down-Left-Right-Space pressed";
        if (m_rockets.find(reinterpret_cast<std::size_t>(m_pPlayerTank.get())) == std::end(m_rockets)) {
            pRocket = GameObjectFactory::get().getRocket(m_pPlayerTank->getDirection(), m_pPlayerTank->getRect());
            pRocket->setTank(m_pPlayerTank.get());
            m_rockets.insert({reinterpret_cast<std::size_t>(m_pPlayerTank.get()), pRocket});
        }
        return;

    case Qt::Key_W:
    case Qt::Key_A:
    case Qt::Key_S:
    case Qt::Key_D:
    case Qt::Key_Control:
        qDebug() << "W-A-S-D-Control pressed";
        break;

    case Qt::Key_Escape:
        qDebug() << "Escape pressed";
        break;
    default:
        break;
    }

    m_pPlayerTank->move(step);
}

bool GameController::isMoveAllowed(QRect newPos) const
{
    auto battleField = GameObjectFactory::get().getBattleField();
    if (newPos.x() < 0
            || newPos.y() <0
            || newPos.x() > battleField->width() - battleField->x()
            || newPos.y() > battleField->height() - battleField->y())
        return false;

    foreach (auto brick, m_bricks) {
        if (newPos.intersects(brick->getRect())){
            qDebug() << "newPos: " << newPos << " | brick: " << brick->getRect();
            return false;
        }
    }
    return true;
}

bool GameController::intersectWorldObj(Rocket *rocket)
{
    auto currRect = rocket->getRect();
    auto battleField = GameObjectFactory::get().getBattleField();
    if (currRect.x() < 0
            || currRect.y() <0
            || currRect.x() > battleField->width() - battleField->x()
            || currRect.y() > battleField->height() - battleField->y()) {
        m_rockets.erase(reinterpret_cast<std::size_t>(rocket->getTank())); // todo: add ThreadSafety
        rocket->setVisible(false);
        return true;
    }

    foreach (auto brick, m_bricks) {
        if (currRect.intersects(brick->getRect())){
            qDebug() << "Rocket hit brick: ";
            brick->setVisible(false);
            rocket->setVisible(false);
            m_rockets.erase(reinterpret_cast<std::size_t>(rocket->getTank()));
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
    m_backgroundWorker = async(std::launch::async, &GameController::ActiveThread, this);
}

void GameController::stop()
{
    qDebug() << "GameController::stop()";
    m_bIsExit.store(true);

    if (m_backgroundWorker.valid()){
        qDebug() << "m_backgroundWorker.valid() == true";
        if (m_backgroundWorker.wait_for(std::chrono::seconds(2)) == std::future_status::ready) // in case resolve freezing if smth bad happens
            m_backgroundWorker.get();
    }
}

void GameController::ActiveThread()
{
    qDebug() << "======================= GameController::ActiveThread() ";
    while (!m_bIsExit){
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        int step = 1;
        foreach (auto item, m_rockets) {
            qDebug() << "rocket[...] = " << item.second;
            item.second->moveTarget(step);
        }
        qDebug() << ">>=========<< Cycle ends;";
    }
}
