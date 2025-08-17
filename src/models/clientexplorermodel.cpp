#include "clientexplorermodel.h"

ClientExplorerModel::ClientExplorerModel(QObject* parent)
    : QAbstractTableModel(parent)
    , _data()
{
}

QVariant ClientExplorerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return "Id";
        case 1:
            return "Status";
        }
    }

    if (orientation == Qt::Horizontal && role == Qt::TextAlignmentRole)
        return Qt::AlignLeft;

    return {};
}

QVariant ClientExplorerModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const RemoteClient& item = _data[index.row()];
    switch (index.column())
    {
    case 0:
        return "[" + item.id + "]";
    case 1:
        return item.isActive ? "Active" : "Inactive";
    }

    return {};
}

void ClientExplorerModel::update(const QList<RemoteClient>& data)
{
    beginResetModel();
    _data = data;
    endResetModel();
}
