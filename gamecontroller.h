#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>

class GameController : public QObject
{
    Q_OBJECT
public:
    static GameController& get() {
        static GameController self;
        return self;
    }

signals:

public slots:
    void keyPressed(Qt::Key key);

private:
    GameController();
    ~GameController();
};

#endif // GAMECONTROLLER_H
