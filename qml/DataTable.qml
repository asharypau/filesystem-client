import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

Frame {
    implicitWidth: 300
    implicitHeight: 200

    property alias tableAlias: table;
    property var viewModel;
    property var otherDataTable;

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 8

        HorizontalHeaderView {
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
            model: viewModel.model
            focus: true
            clip: true
            interactive: false
            pointerNavigationEnabled: false
            Layout.fillWidth: true
            Layout.fillHeight: true

            selectionMode: TableView.SingleSelection
            selectionBehavior: TableView.SelectRows
            selectionModel: ItemSelectionModel { model: table.model }

            delegate: TableViewDelegate {
                padding: 2
                implicitHeight: 20
                implicitWidth: table.width / table.columns

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
                var row = 0;
                if (event.key === Qt.Key_Up) {
                    row = table.selectionModel.currentIndex.row - 1;
                    if (table.selectionModel.currentIndex.row === 0) {
                        row = 0;
                    }

                    table.selectRow(row);
                    event.accepted = true;
                }
                else if (event.key === Qt.Key_Down) {
                    row = table.selectionModel.currentIndex.row + 1;
                    if (table.selectionModel.currentIndex.row === -1) {
                        row = 0;
                    } else if (table.selectionModel.currentIndex.row === table.rows - 1) {
                        row = table.rows - 1;
                    }

                    table.selectRow(row);
                    event.accepted = true;
                }
                else if (event.key === Qt.Key_Left || event.key === Qt.Key_Right) {
                    table.selectionModel.clear();
                    event.accepted = true;
                } else if (event.key === Qt.Key_Tab && otherDataTable) {
                    otherDataTable.tableAlias.forceActiveFocus();
                    event.accepted = true;
                }
            }

            function selectRow(row) {
                const idx = table.model.index(row, 0);
                table.selectionModel.setCurrentIndex(idx, ItemSelectionModel.ClearAndSelect | ItemSelectionModel.Rows);
            }
        }
    }
}
