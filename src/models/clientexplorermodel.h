#ifndef CLIENTEXPLORERMODEL_H
#define CLIENTEXPLORERMODEL_H

#include "client.h"
#include "qlist.h"
#include "qobject.h"
#include "qstandarditemmodel.h"

class ClientExplorerModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    ClientExplorerModel(QObject* parent);

    int columnCount(const QModelIndex& = QModelIndex()) const override { return 2; }
    int rowCount(const QModelIndex& = QModelIndex()) const override { return _data.size(); }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex& index, int role) const override;

public slots:
    void update(const QList<RemoteClient>& data);

private:
    QList<RemoteClient> _data;
};

#endif // CLIENTEXPLORERMODEL_H