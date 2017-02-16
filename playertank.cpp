#include "playertank.h"
#include <QDebug>

PlayerTank::PlayerTank() : Tank(Tank::Type::Player)
{

}

void PlayerTank::key(Qt::Key key)
{
    if (key == Qt::Key_Escape)
        qDebug() << "Escape called!";

    switch (key) {
    case Qt::Key_Up:
        qDebug() << "step up";
        break;
    case Qt::Key_Down:
        qDebug() << "step down";
        break;
    case Qt::Key_Left:
        qDebug() << "step left";
        break;
    case Qt::Key_Right:
        qDebug() << "step right";
        break;
    case Qt::Key_Space:
        qDebug() << "fire !!! (space)";
        break;

    default:
        qDebug() << "unknown key is not defined :(";
        break;
    }
}
