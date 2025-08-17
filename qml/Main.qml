import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

ApplicationWindow {
    id: main
    width: 1200
    height: 600
    visible: true
    title: "FileSystemClient"

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
        orientation: Qt.Horizontal

        DataExplorer {
            id: leftTableView
            dataExplorerViewModel: leftDataExplorerViewModel
            SplitView.fillHeight: true
            SplitView.preferredWidth: parent.width / 2
        }

        DataExplorer {
            id: rightTableView
            dataExplorerViewModel: rightDataExplorerViewModel
            SplitView.fillHeight: true
            SplitView.preferredWidth: parent.width / 2
        }
    }

    ConnectDialog {
        id: connectDialog
    }
}
