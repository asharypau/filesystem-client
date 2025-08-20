import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

Rectangle {
    id: root
    border.color: "black"
    border.width: 1
    color: "transparent"

    implicitWidth: 400
    implicitHeight: 200

    property var dataExplorerViewModel;
    property Item otherDataExplorer;
    property alias tableView: tableView;

    ColumnLayout {
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: parent.right

            topMargin: parent.border.width
            bottomMargin: parent.border.width
            leftMargin: parent.border.width
            rightMargin: parent.border.width
        }

        HorizontalHeaderView {
            id: horizontalHeader
            syncView: tableView
            focus: true
            clip: true
            interactive: false
            Layout.fillWidth: true
            Layout.preferredHeight: 30

            delegate: Rectangle {
                implicitHeight: 30
                implicitWidth: 100
                color: "transparent"

                // Bottom border for all headers
                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    height: 1
                    color: "lightgray"
                }

                // Right border, except for the last column
                Rectangle {
                    visible: column < tableView.columns - 1
                    width: 1
                    color: "lightgray"
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                }

                Text {
                    text: display
                    anchors.centerIn: parent
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
            }
        }

        TableView {
            id: tableView
            model: root.dataExplorerViewModel.model
            focus: true
            clip: true
            interactive: false
            pointerNavigationEnabled: false
            Layout.fillWidth: true
            Layout.fillHeight: true

            selectionMode: TableView.SingleSelection
            selectionBehavior: TableView.SelectRows
            selectionModel: ItemSelectionModel {
                id: selection 
                model: tableView.model
            }

            delegate: TableViewDelegate {
                id: tableViewDelegate
                implicitHeight: 20
                implicitWidth: tableView.width / tableView.columns

                Text {
                    id: contentText
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                TapHandler {
                    onTapped: {
                        tableView.selectRow(row);
                        tableView.forceActiveFocus();
                    }
                }
            }

            TapHandler {
                onTapped: {
                    tableView.forceActiveFocus();
                }
            }

            Keys.onPressed: (event) => {
                if (event.key === Qt.Key_Up) {
                    var row = selection.currentIndex.row - 1;
                    if (selection.currentIndex.row === 0) {
                        row = 0;
                    }

                    tableView.selectRow(row);
                    event.accepted = true;
                }
                else if (event.key === Qt.Key_Down) {
                    var row = selection.currentIndex.row + 1;
                    if (selection.currentIndex.row === -1) {
                        row = 0;
                    } else if (selection.currentIndex.row === tableView.rows - 1) {
                        row = tableView.rows - 1;
                    }

                    tableView.selectRow(row);
                    event.accepted = true;
                }
                else if (event.key === Qt.Key_Left || event.key === Qt.Key_Right) {
                    selection.clear();
                    event.accepted = true;
                } else if (event.key === Qt.Key_Tab) {
                    root.otherDataExplorer.tableView.forceActiveFocus();
                    event.accepted = true;
                }
            }

            function selectRow(row) {
                const idx = tableView.model.index(row, 0);
                selection.setCurrentIndex(idx, ItemSelectionModel.ClearAndSelect | ItemSelectionModel.Rows);
            }
        }
    }
}
