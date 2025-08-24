import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

Frame {
    id: root
    implicitWidth: 400
    implicitHeight: 200

    background: Rectangle {
        border.width: 1
        radius: 2
    }

    contentItem : ColumnLayout {
        anchors.fill: parent
        anchors.margins: root.background.border.width + 1
        spacing: 2

        HorizontalHeaderView {
            id: horizontalHeader
            syncView: table
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
                    visible: column < table.columns - 1
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
            id: table
            model: root.viewModel.model
            focus: true
            clip: true
            interactive: false
            pointerNavigationEnabled: false
            Layout.fillWidth: true
            Layout.fillHeight: true

            selectionMode: TableView.SingleSelection
            selectionBehavior: TableView.SelectRows
            selectionModel: ItemSelectionModel {
                id: selectModel
                model: table.model
            }

            delegate: TableViewDelegate {
                implicitHeight: 20
                implicitWidth: table.width / table.columns
                padding: 2

                TapHandler {
                    onTapped: {
                        table.selectRow(row);
                        table.forceActiveFocus();
                    }
                }
            }

            TapHandler {
                onTapped: {
                    table.forceActiveFocus();
                }
            }

            Keys.onPressed: (event) => {
                if (event.key === Qt.Key_Up) {
                    var row = selectModel.currentIndex.row - 1;
                    if (selectModel.currentIndex.row === 0) {
                        row = 0;
                    }
            
                    table.selectRow(row);
                    event.accepted = true;
                }
                else if (event.key === Qt.Key_Down) {
                    var row = selectModel.currentIndex.row + 1;
                    if (selectModel.currentIndex.row === -1) {
                        row = 0;
                    } else if (selectModel.currentIndex.row === table.rows - 1) {
                        row = table.rows - 1;
                    }
            
                    table.selectRow(row);
                    event.accepted = true;
                }
                else if (event.key === Qt.Key_Left || event.key === Qt.Key_Right) {
                    selectModel.clear();
                    event.accepted = true;
                } else if (event.key === Qt.Key_Tab) {
                    root.otherDataTable.table.forceActiveFocus();
                    event.accepted = true;
                }
            }

            function selectRow(row) {
                const idx = table.model.index(row, 0);
                selectModel.setCurrentIndex(idx, ItemSelectionModel.ClearAndSelect | ItemSelectionModel.Rows);
            }
        }
    }

    property alias table: table;

    property var viewModel;
    property var otherDataTable;
}
