#include "tank.h"
#include "gamecontroller.h"


void Tank::rotate(Direction step)
{
    if (step == m_lastStep || step == Direction::NONE)
        return;

    setProperty("rotation", m_RotationMap.at(step));
    m_lastStep = step;
}

void Tank::fire()
{
    GameController::get().rocketLaunch(this);
}

void Tank::init()
{
    rotate(Direction::DOWN);
}

void Tank::move(Direction step)
{
//    qDebug() << __FUNCTION__ << "<-----" << " Step: " << step;
    if (step == Direction::NONE)
        return;
//    qDebug() << "Tank::move | Point = " << getPosition();

    if (isChangeDirection(step)){
        rotate(step);
    } else {
        auto point = getPosition();
        switch (step) {
        case Direction::UP:
            point.setY(point.y() - STEP_SIZE);
            break;
        case Direction::DOWN:
            point.setY(point.y() + STEP_SIZE);
            break;
        case Direction::LEFT:
            point.setX(point.x() - STEP_SIZE);
            break;
        case Direction::RIGHT:
            point.setX(point.x() + STEP_SIZE);
            break;
        default:
            qDebug() << "WARNING: Unexpected step type!";
            break;
        }
        // change position
        if (GameController::get().isMoveAllowed(QRect(point, getSize()), this)){
            setPosition(point);
        }
    }
}

bool Tank::isChangeDirection(Direction step)
{
    if (step != m_lastStep)
        return true;
    else
        return false;
}
