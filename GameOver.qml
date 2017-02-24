import QtQuick 2.0

Item
{
    anchors.fill: parent

    Rectangle {
        id: game_over
        objectName: "game_over"
        anchors.fill: parent
        color: "black"
        opacity: 0.5
        z: 2
        visible: false

        property alias info: title.text

        Text{
            id: title
            anchors.fill: parent.fill
            color:"white"
            text: "Game over"
            font.pixelSize: 60
            anchors.centerIn: parent
        }

        Text{
            id: restart
            anchors.fill: parent.fill
            color:"white"
            text: "Press Esc to start"
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: title.bottom
        }
    }


}
