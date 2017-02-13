#ifndef TANK_H
#define TANK_H

#include "gameobject.h"
#include <map>

class Tank : public GameObject
{
    Q_OBJECT
public:
    enum Step {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE
    };

    Tank() {}
    virtual ~Tank() = default;
    void move(Step step);
    void fire();

    Q_INVOKABLE void init();
protected:
    enum {
        STEP_SIZE = 10
    };
    enum Type {
        PLAYER,
        ENEMY
    };

    void rotate(Step step);

private:
    QPoint m_point;

    bool isChangeDirection(Step step);

    Step m_lastStep = Step::NONE;
    Type m_type = ENEMY;

    const std::map<Step, int> m_RotationMap = {
        {Step::UP, 0},
        {Step::RIGHT, 90},
        {Step::DOWN, 180},
        {Step::LEFT, 270}
    };

signals:

public slots:

};
#endif // TANK_H
