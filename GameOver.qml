import QtQuick 2.0

Rectangle
{
    objectName: "game_over"
    id: game_over
    anchors.fill: parent
    color: "black"
    opacity: 0.5
    z: 2
    visible: false

    Text{
        id: title
        anchors.fill: parent.fill
        color:"white"
        text: "Game over"
        font.pixelSize: 60
        anchors.centerIn: parent
    }
}
