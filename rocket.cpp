#include "rocket.h"
#include "gamecontroller.h"

void Rocket::move(int step)
{
    qDebug() << "Rocket::move(uint8_t step)";
    switch (getDirection()) {
    case Direction::UP:
        setProperty("y", y() - step);
        break;
    case Direction::DOWN:
        setProperty("y", y() + step);
        break;
    case Direction::RIGHT:
        setProperty("x", x() + step);
        break;
    case Direction::LEFT:
        setProperty("x", x() - step);
        break;
    default:
        break;
    }

    GameController::get().intersectWorldObj(this);
}

void Rocket::moveTarget(int step)
{
    qDebug() << "Rocket::moveTarget(uint8_t step)";
    emit signalMove(step);
}
