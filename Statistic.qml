import QtQuick 2.0

Rectangle {
    width: field.width
    height: 200
    anchors.right: field.right

    Rectangle {
        anchors.fill: parent
        objectName: "statistic"
        color: "#adaaaa"

        property alias information: info.text
    }

    Text
    {
        id: info
        font.pixelSize: 20
    }
}
