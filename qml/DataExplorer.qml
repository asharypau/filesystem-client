import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

Rectangle {
    border.color: "black"
    border.width: 1
    color: "transparent"

    property var dataExplorerViewModel

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
            clip: true
            interactive: false
            Layout.fillWidth: true
            Layout.preferredHeight: 30

            delegate: Rectangle {
                implicitHeight: 30
                implicitWidth: tableView.columnWidth(column)
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
                }
            }
        }

        TableView {
            id: tableView
            focus: true
            model: dataExplorerViewModel.model
            clip: true
            interactive: false
            Layout.fillWidth: true
            Layout.fillHeight: true

            selectionModel: ItemSelectionModel {
                id: selectionModel
                model: tableView.model
            }

            delegate: Rectangle {
                required property bool current;
                required property bool selected;

                implicitWidth: {
                    // if (column === 0) return tableView.width * 0.4;

                    // return tableView.width * 0.2;

                    return tableView.width / tableView.columns
                }
                implicitHeight: 20
                color: selected ? "lightblue" : "transparent"

                Text {
                    text: display
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        const idx = tableView.model.index(row, 0);
                        tableView.selectionModel.setCurrentIndex(
                            idx,
                            ItemSelectionModel.ClearAndSelect | ItemSelectionModel.Current | ItemSelectionModel.Rows
                        );

                        forceActiveFocus();
                    }
                }
            }

            onCurrentRowChanged: {
                const idx = tableView.model.index(currentRow, 0);
                selectionModel.setCurrentIndex(
                    idx,
                    ItemSelectionModel.ClearAndSelect | ItemSelectionModel.Current | ItemSelectionModel.Rows
                );
            }
        }
    }
}
