import QtQuick 2.0
import Game.Eagle 1.0

EagleCpp {
    objectName: "eagle"
    width: 40
    height: 40

    Image {
        id: eagle_img
        width: parent.width
        height: parent.height
        source: "files/res/img/eagle.png"
    }
}
