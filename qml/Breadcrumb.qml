import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: root
    spacing: -8
    clip: true
    implicitHeight: 50

    Repeater {
        model: breadcrumbViewModel.pathItems

        delegate: BreadcrumbButton {
            text: modelData
            first: index === 0
            last: index === breadcrumbViewModel.pathItems.length - 1
            onClicked: console.log("Go to:", modelData)
        }
    }
}
