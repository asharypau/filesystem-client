#ifndef DATAEXPLORERVIEWMODEL_H
#define DATAEXPLORERVIEWMODEL_H

#include "../models/clientexplorermodel.h"
#include "../models/fileexplorermodel.h"
#include "../services/explorerdataprovider.h"
#include "qobject.h"

class DataExplorerViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* model READ model NOTIFY modelChanged)

public:
    enum class ViewState : uint16_t
    {
        None,
        Clients,
        FileInfos,
    };

public:
    DataExplorerViewModel(ViewState state, ExplorerDataProvider* explorerDataProvider, QObject* parent = nullptr);

    QObject* model()
    {
        switch (_viewState)
        {
        case ViewState::Clients:
            return _clientExplorerModel;
        case ViewState::FileInfos:
            return _fileExplorerModel;

        case ViewState::None:
        default:
            return {};
        }
    }

signals:
    void modelChanged();

private slots:
    void onStarted();
    void onClientsReceived(const QList<RemoteClient>& clients);
    void onFileInfosReceived(const QList<FileInfo>& fileInfos);

private:
    ViewState _viewState;
    ExplorerDataProvider* _explorerDataProvider;
    ClientExplorerModel* _clientExplorerModel;
    FileExplorerModel* _fileExplorerModel;
};

#endif // DATAEXPLORERVIEWMODEL_H
