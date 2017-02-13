#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <memory>

class Tank;
class Brick;

class GameController : public QObject
{
    Q_OBJECT
public:
    static GameController& get() {
        static GameController self;
        return self;
    }

    void init();
    bool isMoveAllowed(QRect newPos) const;
signals:

public slots:
    void keyPressed(Qt::Key key);

private:
    GameController();
    ~GameController() = default;

    std::shared_ptr<Tank> m_pPlayerTank;
    QList<Brick*> m_bricks;
};

#endif // GAMECONTROLLER_H
