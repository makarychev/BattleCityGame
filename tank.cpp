#include "tank.h"
#include "gamecontroller.h"


void Tank::rotate(Tank::Step step)
{
    if (step == m_lastStep || step == Step::NONE)
        return;

    setProperty("rotation", m_RotationMap.at(step));
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
    qDebug() << __FUNCTION__ << "<-----" << " Step: " << step;
    if (step == Step::NONE)
        return;
    qDebug() << "Tank::move | Point = " << getPosition();

    if (isChangeDirection(step)){
        rotate(step);
    } else {
        auto point = getPosition();
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
        if (GameController::get().isMoveAllowed(QRect(point, getSize()))){
            setPosition(point);
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
