import QtQuick
import QtQuick.Controls
import QtQuick.Shapes

ToolButton {
    id: root
    implicitHeight: contentItem.implicitHeight
    implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding

    background: Shape {
        anchors.fill: parent

        ShapePath {
            strokeWidth: 1
            strokeColor: "#aaa"
            fillColor: {
                if (root.last || root.hovered) {
                    return "#e0e0e0";
                } else if (root.down) {
                    return "#d0d0d0";
                } else {
                    return "transparent";
                }
            } 

            startX: 0
            startY: 0

            PathLine { x: width - (root.last ? 0 : 12); y: 0 }
            PathLine { x: width; y: height / 2 }
            PathLine { x: width - (root.last ? 0 : 12); y: height }
            PathLine { x: 0; y: height }
            PathLine { x: (root.first ? 0 : 12); y: height / 2 }
            PathLine { x: 0; y: 0 }
        }
    }

    contentItem: Text {
        text: root.text
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        rightPadding: 10
        leftPadding: 10
        topPadding: 4
        bottomPadding: 4
        color: "black"
        font.bold: root.last
    }

    property bool first: false
    property bool last: false
}
