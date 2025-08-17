#ifndef FILEEXPLORERMODEL
#define FILEEXPLORERMODEL

#include "fileinfo.h"
#include "qlist.h"
#include "qobject.h"
#include "qstandarditemmodel.h"

class FileExplorerModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit FileExplorerModel(QObject* parent = nullptr);

    int columnCount(const QModelIndex& = QModelIndex()) const override { return 4; }
    int rowCount(const QModelIndex& = QModelIndex()) const override { return _data.size(); }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex& index, int role) const override;

public slots:
    void update(const QList<FileInfo>& data);

private:
    QList<FileInfo> _data;
};

#endif // FILEEXPLORERMODEL
