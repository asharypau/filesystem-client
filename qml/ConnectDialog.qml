import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Dialog {
    id: connectDialog
    title: "Connection to the Server"
    modal: true
    closePolicy: Dialog.NoAutoClose
    anchors.centerIn: parent

    width: 500
    height: 300

    contentItem: Pane {
        padding: 12
        background: null

        ColumnLayout {
            anchors.fill: parent
            Layout.fillWidth: true
            spacing: 10

            RowLayout {
                Layout.fillWidth: true

                Label {
                    text: "Host"
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: 24
                    verticalAlignment: Text.AlignVCenter
                }
                TextField {
                    id: host
                    Layout.fillWidth: true
                    Layout.preferredHeight: 24
                    verticalAlignment: TextInput.AlignVCenter

                    text: connectDialogViewModel.host
                    onTextChanged: connectDialogViewModel.host = host.text
                }
            }
            RowLayout {
                Layout.fillWidth: true

                Label {
                    text: "Port (0–65535)"
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: 24
                    verticalAlignment: Text.AlignVCenter
                }
                TextField {
                    id: port
                    Layout.fillWidth: true
                    Layout.preferredHeight: 24
                    verticalAlignment: TextInput.AlignVCenter

                    text: connectDialogViewModel.port
                    onTextChanged: connectDialogViewModel.port = port.text

                    validator: IntValidator {
                              bottom: 0
                              top: 65535
                    }
                }
            }
            RowLayout {
                Layout.fillWidth: true

                Label {
                    text: "Root"
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: 24
                    verticalAlignment: Text.AlignVCenter
                }
                TextField {
                    id: root
                    Layout.fillWidth: true
                    Layout.preferredHeight: 24
                    verticalAlignment: TextInput.AlignVCenter

                    text: connectDialogViewModel.root
                    onTextChanged: connectDialogViewModel.root = root.text
                }
                Button {
                    text: "..."
                    Layout.preferredWidth: 40
                    Layout.preferredHeight: 24
                    onClicked: folderDialog.open()
                }
            }
            Text {
                text: connectDialogViewModel.errorMessage
                color: "red"
                visible: connectDialogViewModel.errorMessage.length > 0
            }
            Item { Layout.fillHeight: true }
        }
    }

    footer: Pane {
        padding: 12
        background: null

        RowLayout {
            anchors.fill: parent
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: "Cancel"
                Layout.preferredWidth: 100
                onClicked: connectDialogViewModel.close()
            }

            Item { Layout.fillWidth: true }

            Button {
                text: "Connect"
                Layout.preferredWidth: 100
                onClicked: connectDialogViewModel.connectToHost()
            }
    
            Button {
                text: "Save && Connect"
                Layout.preferredWidth: 100
                onClicked: connectDialogViewModel.connectToHost()
            }
        }
    }

    FolderDialog {
        id: folderDialog
        title: "Select a root directory"

        onAccepted: connectDialogViewModel.root = folderDialog.selectedFolder.toString().replace("file:///", "")
    }

    Connections {
        target: connectDialogViewModel

        function onClosed() {
            connectDialog.reject()
        }

        function onStarted() {
            connectDialog.accept()
        }
    }
}
