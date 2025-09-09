import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

ColumnLayout {
    spacing: 4
    clip: true

    property alias dataTableAlias: dataTable;
    property var dataExplorerViewModel;
    property var otherDataExplorer;

    Breadcrumb { Layout.fillWidth: true }
    DataTable {
        id: dataTable
        viewModel: dataExplorerViewModel
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    Component.onCompleted: {
        dataTable.otherDataTable = otherDataExplorer.dataTableAlias
    }
}
