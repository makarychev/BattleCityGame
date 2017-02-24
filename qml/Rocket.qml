import QtQuick 2.0
import Game.Rocket 1.0

RocketCpp {
    objectName: "rocket"
    width: 10
    height: 10

    Rectangle {
        id : rocket
        width: parent.width
        height: parent.height
        radius: parent.width
        color: "red"
        visible: true
    }

}
