#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include <QQuickItem>

class KeyHandler : public QQuickItem
{
    Q_OBJECT
public:
    KeyHandler();
    ~KeyHandler();

    Q_INVOKABLE void pressed(Qt::Key key);

signals:
    void keyPressed(Qt::Key);
    void gameControls(Qt::Key);
public slots:

};

#endif // KEYHANDLER_H
