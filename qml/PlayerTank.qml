import QtQuick 2.0
import Game.PlayerTank 1.0

PlayerTank {
    id: playerTank
    objectName: "playerTank"
    width: 36
    height: 36

    Image {
        source: "/res/img/player_tank.png"
        width: parent.width
        height: parent.width
    }
    Component.onCompleted: playerTank.init()
}
