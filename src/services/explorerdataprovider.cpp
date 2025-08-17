#include "explorerdataprovider.h"
#include "localfileinfoprovider.h"

ExplorerDataProvider::ExplorerDataProvider(SessionManager* sessionManager, QObject* parent)
    : QObject(parent)
    , _sessionManager(sessionManager)
    , _connection(nullptr)
{
    connect(_sessionManager, &SessionManager::started, this, &ExplorerDataProvider::onStarted);
}

void ExplorerDataProvider::readClients()
{
    if (!_connection)
    {
        return;
    }

    _connection->writeHeaders(Network::Protocol::Headers::make(0,
                                                               Network::Protocol::Type::ClientRequest,
                                                               Network::Protocol::Action::GetClients));
}

void ExplorerDataProvider::readFileInfos(Client::id_t id)
{
    if (!_connection)
    {
        return;
    }

    if (_connection->owner().id == id)
    {
    }
    else
    {
        QList<FileInfo> fileInfos = LocalFileInfoProvider::get(_connection->owner().root);
        emit fileInfosReceived(fileInfos);
    }
}

void ExplorerDataProvider::onStarted(Network::IConnection* connection)
{
    _connection = connection;
    connect(_sessionManager, &SessionManager::dataReceived, this, &ExplorerDataProvider::onDataReceived);
    emit started();
}

void ExplorerDataProvider::onDataReceived(Network::Protocol::Headers headers, Network::Protocol::data_t data)
{
    if (headers.type != Network::Protocol::Type::ClientRequest)
    {
        return;
    }

    switch (headers.method)
    {
    case Network::Protocol::Action::GetClientFiles:
    {
        QList<FileInfo> fileInfos = Network::Serializer::deserialize<QList<FileInfo>>(data);
        emit fileInfosReceived(fileInfos);
        break;
    }

    case Network::Protocol::Action::GetClients:
    {
        QList<RemoteClient> clients = Network::Serializer::deserialize<QList<RemoteClient>>(data);
        emit clientsReceived(clients);
        break;
    }

    case Network::Protocol::Action::None:
    default:
        break;
    }
}
