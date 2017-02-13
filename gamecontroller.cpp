#include "gamecontroller.h"
#include "gameobjectfactory.h"
#include "playertank.h"
#include <QDebug>
#include <QPoint>
#include "brick.h"

void GameController::init()
{
    m_pPlayerTank = GameObjectFactory::get().cretePlayerTank();
    m_bricks = GameObjectFactory::get().getBricks();
}

void GameController::keyPressed(Qt::Key key)
{
    using ts = Tank::Step;
    ts step = ts::NONE;
    switch (key) {
    case Qt::Key_Up:
        step = ts::UP;
        break;
    case Qt::Key_Down:
        step = ts::DOWN;
        break;
    case Qt::Key_Left:
        step = ts::LEFT;
        break;
    case Qt::Key_Right:
        step = ts::RIGHT;
        break;
    case Qt::Key_Space:
        qDebug() << "Up-Down-Left-Right-Space pressed";
        break;

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

GameController::GameController() : QObject(nullptr)
{

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
