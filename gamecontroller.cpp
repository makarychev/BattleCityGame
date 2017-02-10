#include "gamecontroller.h"
#include <QDebug>

void GameController::keyPressed(Qt::Key key)
{
    qDebug() << __FUNCTION__;

    switch (key) {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Space:
        qDebug() << "Up-Down-Left-Right-Space pressed";
        break;

    case Qt::Key_W:
    case Qt::Key_A:
    case Qt::Key_S:
    case Qt::Key_D:
    case Qt::Key_Control:
        qDebug() << "W-A-S-D-Control pressed";
        break;

    case Qt::Key_Escape:
        qDebug() << "Escape pressed";
        break;
    default:
        break;
    }

}

GameController::GameController() : QObject(nullptr)
{

}

GameController::~GameController()
{

}
