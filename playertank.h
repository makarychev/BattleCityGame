#ifndef PLAYERTANK_H
#define PLAYERTANK_H

#include <tank.h>

class PlayerTank : public Tank
{
    Q_OBJECT
public:
    explicit PlayerTank();
    Q_INVOKABLE void key(Qt::Key key);
signals:

public slots:
};

#endif // PLAYERTANK_H
