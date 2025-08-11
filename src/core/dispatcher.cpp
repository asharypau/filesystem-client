#include "dispatcher.h"
#include "../models/remoteclient.h"
#include "../network/serialization.h"
#include <qlist.h>

Dispatcher::Dispatcher(QObject* parent)
    : QObject(parent)
{
}

void Dispatcher::dispatch(Network::HeaderPackage header_package, QByteArray data)
{
    switch (header_package.type)
    {
    case Network::RequestType::None:
        break;
    case Network::RequestType::ClientList:
        handleClientListRequest(data);
        break;
    default:
        break;
    }
}

void Dispatcher::handleClientListRequest(const QByteArray& data)
{
    QList<RemoteClient> remote_clients = Network::Serializer::deserialize<QList<RemoteClient>>(data);
}
