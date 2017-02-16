#ifndef ROCKET_H
#define ROCKET_H

#include "gameobject.h"
#include "direction.h"
#include "tank.h"

class Rocket : public GameObject
{
    Q_OBJECT
public:
    Rocket() : m_direction(Direction::NONE) {
        connect(this, SIGNAL(signalMove(int)), SLOT(move(int)));
    }
    ~Rocket() { qDebug() << "~Rocket()";}

    void setDirection(const Direction direction) noexcept {
        m_direction = direction;
    }
    Direction getDirection() const noexcept {
        return m_direction;
    }
    void setTank(Tank* tank) noexcept {
        m_tank = tank;
        setDirection(tank->getDirection());
        setPosition(tank->getRect());
    }
    Tank* getTank() const noexcept {
        return m_tank;
    }
    void setPosition(const QRect&) noexcept;
    void moveTarget(int step);

private:

    Direction m_direction;
    Tank* m_tank;
signals:
    void signalMove(int step);

public slots:
    void move(int step);
};

#endif // ROCKET_H
