#include "gamecontroller.h"
#include "gameobjectfactory.h"
#include "playertank.h"
#include <QDebug>
#include <QPoint>

void GameController::init(QObject *rootObject)
{
    m_pPlayerTank = GameObjectFactory::get().cretePlayerTank();
}

bool GameController::isPositionAllowed(QPoint point)
{
    return true; // todo: implement me!
}

void GameController::keyPressed(Qt::Key key)
{
    qDebug() << __FUNCTION__;
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

    qDebug() << step;
    m_pPlayerTank->move(step);
}

GameController::GameController() : QObject(nullptr)
{

}

GameController::~GameController()
{

}
