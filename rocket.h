#ifndef ROCKET_H
#define ROCKET_H

#include "gameobject.h"
#include "direction.h"
#include "tank.h"

class Rocket : public GameObject
{
    Q_OBJECT
public:
    Rocket();
    ~Rocket() = default;

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

    void blast() noexcept;
    void launch() noexcept;
    void setPosition(const QRect&) noexcept;
    void moveTarget(int step);

private:
    Direction m_direction;
    Tank* m_tank = nullptr;

signals:
    void signalMove(int step);

public slots:
    void move(int step);
};

#endif // ROCKET_H
