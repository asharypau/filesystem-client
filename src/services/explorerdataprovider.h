#ifndef EXPLORERDATAPROVIDER_H
#define EXPLORERDATAPROVIDER_H

#include "../core/sessionmanager.h"
#include "../models/client.h"
#include "../models/fileinfo.h"
#include "../network/iconnection.h"
#include "../network/protocol.h"
#include "../network/protocoltypes.h"
#include "qlist.h"
#include "qobject.h"

class ExplorerDataProvider : public QObject
{
    Q_OBJECT

public:
    ExplorerDataProvider(SessionManager* sessionManager, QObject* parent = nullptr);

    void readClients();
    void readFileInfos(Client::id_t id);

signals:
    void started();
    void clientsReceived(const QList<RemoteClient>& clients);
    void fileInfosReceived(const QList<FileInfo>& fileInfos);

private slots:
    void onStarted(Network::IConnection* connection);
    void onDataReceived(Network::Protocol::Headers headers, Network::Protocol::data_t data);

private:
    SessionManager* _sessionManager;
    Network::IConnection* _connection;
};

#endif // EXPLORERDATAPROVIDER_H
