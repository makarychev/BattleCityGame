#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <memory>

class Tank;

class GameController : public QObject
{
    Q_OBJECT
public:
    static GameController& get() {
        static GameController self;
        return self;
    }

    void init(QObject* rootObject);
    bool isPositionAllowed(QPoint point);
signals:

public slots:
    void keyPressed(Qt::Key key);

private:
    GameController();
    ~GameController();

    std::shared_ptr<Tank> m_pPlayerTank;
};

#endif // GAMECONTROLLER_H
