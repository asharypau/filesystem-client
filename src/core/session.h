#ifndef SESSION_H
#define SESSION_H

#include "../models/localclient.h"
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
    void dataReceived(QByteArray data);

private slots:
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError error);
    void onReadyRead();

private:
    template<class TModel>
    void write(TModel model)
    {
        QByteArray raw_data = Serializer::serialize(model);
        data_size_t raw_data_size = raw_data.size();

        QByteArray data;
        data.resize(DATA_SIZE + raw_data_size);

        std::memcpy(data.data(), &raw_data_size, DATA_SIZE);
        std::memcpy(data.data() + DATA_SIZE, raw_data.data(), raw_data_size);

        _socket->write(data);
    }

    QTcpSocket* _socket;
    LocalClient _local_client;
};

#endif // SESSION_H
