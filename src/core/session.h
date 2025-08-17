#ifndef SESSION_H
#define SESSION_H

#include "../models/client.h"
#include "../network/iconnection.h"
#include "../network/protocol.h"
#include "../network/protocoltypes.h"
#include "../network/serialization.h"
#include "qstring"
#include <qobject.h>
#include <qtcpsocket.h>

class Session : public Network::IConnection
{
    Q_OBJECT

public:
    explicit Session(QObject* parent = nullptr);

    const LocalClient& owner() const override { return _localClient; };
    void writeHeaders(const Network::Protocol::Headers& headers) override;
    void write(const Network::Protocol::data_t& data) override;
    void connectToHost(QString host, quint16 port, QString root);

signals:
    void started(Network::IConnection* connection);
    void ended();
    void errorOccurred(QAbstractSocket::SocketError error, QString errorString);
    void dataReceived(Network::Protocol::Headers headers, Network::Protocol::data_t data);

private slots:
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError error);
    void onReadyRead();

private:
    QTcpSocket* _socket;
    LocalClient _localClient;
};

#endif // SESSION_H
