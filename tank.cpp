#include "tank.h"
#include "gamecontroller.h"

void Tank::rotate(Tank::Step step)
{
    if (step == m_lastStep || step == Step::NONE)
        return;

    setProperty("rotation", 90); // todo: set rotation map
    m_lastStep = step;
}

void Tank::fire()
{

}

void Tank::init()
{
    rotate(Step::DOWN);
}

void Tank::move(Tank::Step step)
{
    qDebug() << __FUNCTION__ << "<-----";
    if (step == Step::NONE)
        return;

    if (isChangeDirection(step)){
        qDebug() << "isChangeDirection() - true";
        rotate(step);
    } else {
        qDebug() << "isChangeDirection() - false";
        auto point = getPosition();
        qDebug() << "Point = " << point;
        switch (step) {
        case Step::UP:
            point.setY(point.y() - STEP_SIZE);
            break;
        case Step::DOWN:
            point.setY(point.y() + STEP_SIZE);
            break;
        case Step::LEFT:
            point.setX(point.x() - STEP_SIZE);
            break;
        case Step::RIGHT:
            point.setX(point.x() + STEP_SIZE);
            break;
        default:
            qDebug() << "WARNING: Unexpected step type!";
            break;
        }
        // change position
        if (GameController::get().isPositionAllowed(point)){
//            setPosition(point);
            qDebug() << "Point = " << point;
            setProperty("x", point.x());
            setProperty("y", point.y());
        }

    }

}

bool Tank::isChangeDirection(Tank::Step step)
{
    if (step != m_lastStep)
        return true;
    else
        return false;
}
