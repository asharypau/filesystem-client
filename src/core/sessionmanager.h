#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "../network/iconnection.h"
#include "../network/protocol.h"
#include "../network/protocoltypes.h"
#include "qabstractsocket.h"
#include "qobject.h"
#include "qstring.h"
#include "session.h"

class SessionManager : public QObject
{
    Q_OBJECT

public:
    explicit SessionManager(QObject* parent = nullptr);

    void connectToHost(QString host, quint16 port, QString root);

signals:
    void started(Network::IConnection* connection);
    void ended();
    void errorOccurred(QAbstractSocket::SocketError error, QString errorString);
    void dataReceived(Network::Protocol::Headers headers, Network::Protocol::data_t data);

private slots:
    void onStarted(Network::IConnection* connection);
    void onEnded();
    void onErrorOccurred(QAbstractSocket::SocketError error, QString errorString);
    void onDataReceived(Network::Protocol::Headers headers, Network::Protocol::data_t data);

private:
    Session* _session;
};

#endif // SESSIONMANAGER_H
