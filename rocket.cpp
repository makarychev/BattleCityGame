#include "rocket.h"
#include "gamecontroller.h"


Rocket::Rocket() :  GameObject(), m_direction(Direction::NONE) {
    connect(this, SIGNAL(signalMove(int)), SLOT(move(int)));
}

void Rocket::blast()
{
    setActive(false);
    setVisible(false);
}

void Rocket::move(int step)
{
//    qDebug() << "Rocket::move(uint8_t step)";
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

void Rocket::setPosition(const QRect& startPosition) noexcept
{
    int x = startPosition.x(), y = startPosition.y();
    switch (m_tank->getDirection()) {
    case Direction::UP:
        x = startPosition.x() + startPosition.width()/2;
        break;
    case Direction::DOWN:
        x = startPosition.x() + startPosition.width()/2;
        y = startPosition.y() + startPosition.height();
        break;
    case Direction::RIGHT:
        x = startPosition.x() + startPosition.width();
        y = startPosition.y() + startPosition.height()/2;
        break;
    case Direction::LEFT:
        y = startPosition.y() + startPosition.height()/2;
        break;
    default:
        break;
    }
    setProperty("x", x);
    setProperty("y", y);
}

void Rocket::moveTarget(int step)
{
//    qDebug() << "Rocket::moveTarget(uint8_t step)";
    emit signalMove(step);
}
