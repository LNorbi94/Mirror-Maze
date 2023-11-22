import QtQuick
import QtQuick.Shapes

import MazeModel

Rectangle {
    id: rootId

    required property bool isEntrance
    required property bool isWall
    required property bool isMirror
    required property bool isNegativeMirror

    required property bool isCurrentFieldActive
    required property string direction

    required property var light

    color: "#404040"
    border.width: isWall ? 1 : 0
    border.color: "aliceblue"

    onIsCurrentFieldActiveChanged: {
        if ( isCurrentFieldActive ) {
            state = direction;
        }
    }

    Shape {
        ShapePath {
            strokeColor: rootId.isMirror || rootId.isNegativeMirror ? "aliceblue" : "transparent"
            strokeWidth: 1

            startX: rootId.isNegativeMirror ? 0 : rootId.implicitWidth
            startY: 0

            PathLine {
                x: rootId.isNegativeMirror ? rootId.implicitWidth : 0
                y: rootId.implicitHeight
            }
        }
    }

    transitions: Transition {
        AnchorAnimation {
            duration: 150
        }

        onRunningChanged: {
            if ( !running ) {
                if ( Maze.hasNextId() ) {
                    Maze.getNextId();
                }
            }
        }
    }

    states: [
        State {
            name: "Left"
            AnchorChanges {
                target: light;
                anchors.left: rootId.left;
                anchors.right: undefined;
                anchors.top: undefined;
                anchors.bottom: undefined;
                anchors.horizontalCenter: undefined;
                anchors.verticalCenter: rootId.verticalCenter
            }
        },
        State {
            name: "Right"
            AnchorChanges {
                target: light;
                anchors.left: undefined;
                anchors.right: rootId.right;
                anchors.top: undefined;
                anchors.bottom: undefined;
                anchors.horizontalCenter: undefined;
                anchors.verticalCenter: rootId.verticalCenter
            }
        },
        State {
            name: "Top"
            AnchorChanges {
                target: light;
                anchors.left: undefined;
                anchors.right: undefined;
                anchors.top: rootId.top;
                anchors.bottom: undefined;
                anchors.horizontalCenter: rootId.horizontalCenter;
                anchors.verticalCenter: undefined
            }
        },
        State {
            name: "Bottom"
            AnchorChanges {
                target: light;
                anchors.left: undefined;
                anchors.right: undefined;
                anchors.top: undefined;
                anchors.bottom: rootId.bottom;
                anchors.horizontalCenter: rootId.horizontalCenter;
                anchors.verticalCenter: undefined
            }
        }
    ]

    Component.onCompleted: {
        if ( rootId.isEntrance ) {
            light.anchors.horizontalCenter = rootId.horizontalCenter;
            light.anchors.verticalCenter = rootId.verticalCenter;
        }
    }
}
