#include "session.h"
#include "../services/idgenerator.h"
#include "../services/serialization.h"

Session::Session(QObject *parent)
    : QObject(parent)
    , _socket(new QTcpSocket(this))
    , _local_client()
{
    connect(_socket, &QTcpSocket::connected, this, &Session::onConnected);
    connect(_socket, &QTcpSocket::disconnected, this, &Session::onDisconnected);
    connect(_socket, &QTcpSocket::errorOccurred, this, &Session::onErrorOccurred);
}

void Session::connectToHost(QString host, quint16 port, QString root)
{
    _socket->abort();
    _socket->connectToHost(host, port);

    _local_client.id = IdGenerator::generate(root);
    _local_client.root = root;
}

void Session::onConnected()
{
    write(_local_client);

    connect(_socket, &QTcpSocket::readyRead, this, &Session::onReadyRead);
    emit started();
}

void Session::onDisconnected()
{
    emit ended();
}

void Session::onErrorOccurred(QAbstractSocket::SocketError error)
{
    emit errorOccurred(error, _socket->errorString());
}

void Session::onReadyRead()
{
    data_size_t data_size = 0;
    _socket->read(reinterpret_cast<char *>(&data_size), DATA_SIZE);

    QByteArray data = _socket->read(data_size);
    emit dataReceived(data);
}
