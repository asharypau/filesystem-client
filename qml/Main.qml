import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls.Material

ApplicationWindow {
    id: main
    width: 1200
    height: 600
    visible: true
    title: "FileSystemClient"

    Material.theme: Material.Light;

    menuBar: MenuBar {
        Menu {
            title: "File"

            MenuItem {
                text: "Connect"
                onTriggered: connectDialog.open()
            }

            MenuSeparator {}

            MenuItem {
                text: "Exit"
                onTriggered: Qt.quit()
            }
        }
    }

    SplitView {
        anchors.fill: parent
        anchors.margins: 4
        orientation: Qt.Horizontal

        handle: Rectangle {
            implicitWidth: 5
            implicitHeight: 5
            color: "transparent"
        }

        DataExplorer {
            id: leftDataExplorer
            dataExplorerViewModel: leftDataExplorerViewModel
            SplitView.preferredWidth: parent.width / 2
            SplitView.fillHeight: true
            SplitView.fillWidth: true
        }

        DataExplorer {
            id: rightDataExplorer
            dataExplorerViewModel: rightDataExplorerViewModel
            SplitView.preferredWidth: parent.width / 2
            SplitView.fillHeight: true
            SplitView.fillWidth: true
        }
    }

    ConnectDialog {
        id: connectDialog
    }

    Component.onCompleted: {
        leftDataExplorer.otherDataExplorer = rightDataExplorer;
        rightDataExplorer.otherDataExplorer = leftDataExplorer;
    }
}
