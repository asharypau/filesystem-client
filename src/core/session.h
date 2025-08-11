#ifndef SESSION_H
#define SESSION_H

#include "../models/localclient.h"
#include "../network/constants.h"
#include "../network/headerdraft.h"
#include "../network/headerpackage.h"
#include "../network/serialization.h"
#include "QByteArray"
#include "qstring"
#include <qobject.h>
#include <qtcpsocket.h>

class Session : public QObject
{
    Q_OBJECT

public:
    explicit Session(QObject* parent = nullptr);

    void connectToHost(QString host, quint16 port, QString root);

signals:
    void started();
    void ended();
    void errorOccurred(QAbstractSocket::SocketError error, QString errorString);
    void dataReceived(Network::HeaderPackage header_package, QByteArray data);

private slots:
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError error);
    void onReadyRead();

private:
    template<class TModel>
    void write(const Network::HeaderDraft& header_draft, TModel model)
    {
        QByteArray data = Network::Serializer::serialize(model);
        Network::HeaderPackage header_package = Network::HeaderPackage::from_draft(header_draft,
                                                                                   static_cast<Network::data_size_t>(model.size()));

        _socket->write(Network::Serializer::serialize(header_package));
        _socket->write(data);
    }

    QTcpSocket* _socket;
    LocalClient _local_client;
};

#endif // SESSION_H
