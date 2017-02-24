#ifndef TANK_H
#define TANK_H

#include "gameobject.h"
#include "direction.h"
#include <map>

class Tank : public GameObject
{
    Q_OBJECT
public:
    enum Type {
        Player,
        Enemy
    };
    Tank(Type type) : m_type(type) {m_isActive.store(true);}
    virtual ~Tank() = default;
    void move(Direction step);
    void rotate(Direction step);
    void fire();
    Direction getDirection() const noexcept {
        return m_lastStep;
    }
    Type getType() const noexcept {
        return m_type;
    }

    Q_INVOKABLE void init();
protected:
    enum {
        STEP_SIZE = 10
    };

private:
    QPoint m_point;

    bool isChangeDirection(Direction step);

    Direction m_lastStep = Direction::NONE;
    Type m_type = Type::Enemy;

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
