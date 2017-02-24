import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import Game.KeyHandler 1.0

Window {
    visible: true
    width: 600
    height: 600
    title: qsTr("The Game")


    Statistic {

    }

    Rectangle {
        id: field
        width: 520
        height: 520
        color: "black"
        anchors.centerIn: parent
        objectName: "battleField"

        KeyHandlerCpp {
            width: parent.width
            height: parent.height
            id: presser
            focus: true
            Keys.onPressed: {
                pressed(event.key);
            }
        }

        BattleField {}

        GameOver {}

    }
}
