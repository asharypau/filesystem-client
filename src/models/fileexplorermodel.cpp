#include "fileexplorermodel.h"
#include <qdatetime.h>

FileExplorerModel::FileExplorerModel(QObject* parent)
    : QAbstractTableModel(parent)
    , _filesInfo()
{
    QDateTime dateTime;

    _filesInfo.push_back({"name1", "ext1", dateTime.currentDateTimeUtc(), 1024, false});
    _filesInfo.push_back({"name", "", dateTime.currentDateTimeUtc(), 0, true});
}

QVariant FileExplorerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return "Name";
        case 1:
            return "Extension";
        case 2:
            return "Size";
        case 3:
            return "Date";
        }
    }

    if (orientation == Qt::Horizontal && role == Qt::TextAlignmentRole)
        return Qt::AlignLeft;

    return {};
}

QVariant FileExplorerModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const FileInfo& fileInfo = _filesInfo[index.row()];
    switch (index.column())
    {
    case 0:
        return fileInfo.isDirectory ? "[" + fileInfo.name + "]" : fileInfo.name;
    case 1:
        return fileInfo.isDirectory ? "" : fileInfo.extension;
    case 2:
        return fileInfo.isDirectory ? "<DIR>" : QString::number(fileInfo.size);
    case 3:
        return fileInfo.lastModifiedDate.toString("yyyy-MM-dd HH:mm");
    }

    return {};
}

void FileExplorerModel::update(const QList<FileInfo> filesInfo)
{
    beginResetModel();
    _filesInfo = filesInfo;
    endResetModel();
}
