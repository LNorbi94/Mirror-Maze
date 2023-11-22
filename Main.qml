import QtQuick
import QtQuick.Shapes
import Qt5Compat.GraphicalEffects

import MazeModel

Window {
    id: rootId
    visible: true
    width: 3600
    height: 2000
    title: qsTr("Mirror Maze")

    TableView {
        id: tableViewId

        anchors.fill: parent
        clip: true

        model: Maze

        Rectangle {
            id: lightId

            z: 99
            color: "aliceblue"

            width: 20
            height: 20
            radius: 10
            layer.enabled: true
            layer.effect: Glow {
                color: "white"
                transparentBorder: true
                radius: 5
            }
        }

        delegate: MazeFieldDelegate {
            implicitWidth: rootId.width / tableViewId.columns
            implicitHeight: rootId.height / tableViewId.rows

            light: lightId
            direction: Maze.direction
            isCurrentFieldActive: Maze.currentField.x === row && Maze.currentField.y === column
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            if ( Maze.hasNextId() ) {
                Maze.getNextId();
            }
        }
    }
}
