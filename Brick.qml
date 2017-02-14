import QtQuick 2.0
import Game.Brick 1.0

BrickCpp {
   objectName: "brick"
   width: 20
   height: 20

   Image{
       width: parent.width
       height: parent.height
       source: "files/res/img/brick.png"
   }
}
