import QtQuick 2.0

Item {
    id: battleField

    Component.onCompleted: {
        var map_position = [
                "                          ", //0
                "                          ",
                "  BB  BB  BB  BB  BB  BB  ",
                "  BB  BB  BB  BB  BB  BB  ",
                "  BB  BB  BB  BB  BB  BB  ",
                "  BB  BB  BB  BB  BB  BB  ", //5
                "  BB  BB  BB  BB  BB  BB  ",
                "  BB  BB  BB  BB  BB  BB  ",
                "  BB  BB          BB  BB  ",
                "  BB  BB          BB  BB  ",
                "          BB  BB          ", //10
                "          BB  BB          ",
                "    BBBB          BBBB    ",
                "    BBBB          BBBB    ",
                "          BB  BB          ",
                "          BBBBBB          ", //15
                "  BB  BB  BBBBBB  BB  BB  ",
                "  BB  BB  BB  BB  BB  BB  ",
                "  BB  BB  BB  BB  BB  BB  ",
                "  BB  BB  BB  BB  BB  BB  ",
                "  BB  BB          BB  BB  ", //20
                "  BB  BB          BB  BB  ",
                "  BB  BB          BB  BB  ",
                "  BB  BB   BBBB   BB  BB  ",
                "           BE B           ",
                "           B  B           " //25
                ];
        var brick = Qt.createComponent("Brick.qml");
        var eagle = Qt.createComponent("Eagle.qml")
        var cellSize = 20;
        var object;

        for (var posX = 0; posX < map_position.length; posX++) {
            var row = map_position[posX];
            for (var posY = 0; posY < row.length; posY++) {
                if (row[posY] === ' ')
                    continue;
                else if (row[posY] === 'B')
                    object = brick.createObject(battleField);
                else if (row[posY] === 'E'){
                    object = eagle.createObject(battleField);
                    console.log("eagle constructed" + object)
                }


                object.x = posY * cellSize;
                object.y = posX * cellSize;
//                console.log("x = ", object.x, " | y = ", object.y);
//                console.log(object)
            }
        }
    }

}
