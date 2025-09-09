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
        spacing: 2
        anchors.fill: parent
        anchors.centerIn: parent
        anchors.margins: 6

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
                color: "#f0f0f0"
                border.color: "#cccccc"
                border.width: 1

                Text {
                    text: display
                    anchors.fill: parent
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: parent.color = "#e0e0e0"
                    onExited: parent.color = "#f0f0f0"
                    acceptedButtons: Qt.NoButton
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
            Layout.margins: 0

            selectionMode: TableView.SingleSelection
            selectionBehavior: TableView.SelectRows
            selectionModel: ItemSelectionModel { model: table.model }

            delegate: TableViewDelegate {
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
                    table.selectionModel.clear();
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
