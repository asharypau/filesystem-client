#include "dispatcher.h"
#include "../models/remoteclient.h"
#include "../services/serialization.h"
#include <qlist.h>

Dispatcher::Dispatcher(QObject *parent)
    : QObject(parent)
{
}

void Dispatcher::dispatch(QByteArray data)
{
    QList<RemoteClient> remote_clients = Serializer::deserialize<QList<RemoteClient>>(data);
}
