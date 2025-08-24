import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    Breadcrumb {
        Layout.fillWidth: true
    }

    DataTable {
        id: dataTable
        viewModel: dataExplorerViewModel
        otherDataTable: otherDataExplorer.dataTable
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    property alias dataTable: dataTable;

    property var dataExplorerViewModel;
    property var otherDataExplorer;
}