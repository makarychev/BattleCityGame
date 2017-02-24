#ifndef PLAYERTANK_H
#define PLAYERTANK_H

#include <tank.h>

class PlayerTank : public Tank
{
    Q_OBJECT
public:
    explicit PlayerTank();
    ~PlayerTank() = default;
    void restart(const QPoint &position);
};

#endif // PLAYERTANK_H
