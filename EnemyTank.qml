import QtQuick 2.0
import Game.EnemyTank 1.0

EnemyTankCpp {
    id: enemyTank
    objectName: "enemyTank"
    width: 36
    height: 36

    Image {
        source: "files/res/img/enemy.png"
        width: parent.width
        height: parent.width
    }
    Component.onCompleted: enemyTank.init()
}
