#include "playertank.h"
#include <QDebug>

PlayerTank::PlayerTank() : Tank(Tank::Type::Player)
{

}

void PlayerTank::restart(const QPoint& position)
{
    setPosition(position);
    setVisible(true);
    setActive(true);
}
