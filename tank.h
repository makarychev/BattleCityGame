#ifndef TANK_H
#define TANK_H

#include "gameobject.h"

class Tank : public GameObject
{
    Q_OBJECT
public:
    enum Step {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    Tank() = default;
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
signals:

public slots:



};

#endif // TANK_H
