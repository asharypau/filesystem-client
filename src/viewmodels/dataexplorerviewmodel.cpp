#include "dataexplorerviewmodel.h"

DataExplorerViewModel::DataExplorerViewModel(ViewState viewState,
                                             ExplorerDataProvider* explorerDataProvider,
                                             QObject* parent)
    : QObject(parent)
    , _viewState(viewState)
    , _explorerDataProvider(explorerDataProvider)
    , _clientExplorerModel(new ClientExplorerModel(this))
    , _fileExplorerModel(new FileExplorerModel(this))
{
    connect(_explorerDataProvider, &ExplorerDataProvider::started, this, &DataExplorerViewModel::onStarted);
}

void DataExplorerViewModel::onStarted()
{
    connect(_explorerDataProvider,
            &ExplorerDataProvider::clientsReceived,
            this,
            &DataExplorerViewModel::onClientsReceived);
    connect(_explorerDataProvider,
            &ExplorerDataProvider::fileInfosReceived,
            this,
            &DataExplorerViewModel::onFileInfosReceived);

    switch (_viewState)
    {
    case DataExplorerViewModel::ViewState::Clients:
        _explorerDataProvider->readClients();
        break;
    case DataExplorerViewModel::ViewState::FileInfos:
        _explorerDataProvider->readFileInfos("");
        break;

    case DataExplorerViewModel::ViewState::None:
    default:
        break;
    }
}

void DataExplorerViewModel::onClientsReceived(const QList<RemoteClient>& clients)
{
    if (_viewState != ViewState::Clients)
    {
        return;
    }

    _clientExplorerModel->update(clients);
    emit modelChanged();
}

void DataExplorerViewModel::onFileInfosReceived(const QList<FileInfo>& fileInfos)
{
    if (_viewState != ViewState::FileInfos)
    {
        return;
    }

    _fileExplorerModel->update(fileInfos);
    emit modelChanged();
}
