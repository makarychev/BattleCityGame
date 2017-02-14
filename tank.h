#ifndef TANK_H
#define TANK_H

#include "gameobject.h"
#include "direction.h"
#include <map>

class Tank : public GameObject
{
    Q_OBJECT
public:
    Tank() {}
    virtual ~Tank() = default;
    void move(Direction step);
    void fire();
    Direction getDirection() const noexcept {
        return m_lastStep;
    }

    Q_INVOKABLE void init();
protected:
    enum {
        STEP_SIZE = 10
    };
    enum Type {
        PLAYER,
        ENEMY
    };

    void rotate(Direction step);

private:
    QPoint m_point;

    bool isChangeDirection(Direction step);

    Direction m_lastStep = Direction::NONE;
    Type m_type = ENEMY;

    const std::map<Direction, int> m_RotationMap = {
        {Direction::UP, 0},
        {Direction::RIGHT, 90},
        {Direction::DOWN, 180},
        {Direction::LEFT, 270}
    };

signals:

public slots:

};
#endif // TANK_H
