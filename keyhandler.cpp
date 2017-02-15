#include "keyhandler.h"
#include "gamecontroller.h"
#include <QDebug>

KeyHandler::KeyHandler()
{
    connect(this, SIGNAL(gameControls(Qt::Key)), &GameController::get(), SLOT(keyPressed(Qt::Key)));
}

void KeyHandler::pressed(Qt::Key key)
{
    switch (key) {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Space:
    case Qt::Key_Escape:
        emit gameControls(key);
        break;
    default:
        break;
    }
}
