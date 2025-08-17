#include "session.h"

Session::Session(QObject* parent)
    : Network::IConnection(parent)
    , _socket(new QTcpSocket(this))
    , _localClient()
{
    connect(_socket, &QTcpSocket::connected, this, &Session::onConnected);
    connect(_socket, &QTcpSocket::disconnected, this, &Session::onDisconnected);
    connect(_socket, &QTcpSocket::errorOccurred, this, &Session::onErrorOccurred);
}

void Session::writeHeaders(const Network::Protocol::Headers& headers)
{
    Network::Protocol::data_t data = Network::Serializer::serialize(headers);
    _socket->write(data);
}

void Session::write(const Network::Protocol::data_t& data)
{
    _socket->write(data);
}

void Session::connectToHost(QString host, quint16 port, QString root)
{
    _socket->abort();
    _socket->connectToHost(host, port);

    _localClient.root = root;
}

void Session::onConnected()
{
    Network::Protocol::data_t localClientData = Network::Serializer::serialize(_localClient);
    writeHeaders(Network::Protocol::Headers::make(localClientData.size(), Network::Protocol::Type::Activation));
    write(localClientData);

    _socket->waitForReadyRead();
    Network::Protocol::data_t headersData = _socket->read(Network::Protocol::Headers::SIZE);
    Network::Protocol::Headers headers = Network::Serializer::deserialize<Network::Protocol::Headers>(headersData);

    _socket->waitForReadyRead();
    Network::Protocol::data_t updatedLocalClientData = _socket->read(headers.data_size);
    LocalClient updatedLocalClient = Network::Serializer::deserialize<LocalClient>(updatedLocalClientData);

    _localClient.id = updatedLocalClient.id;

    connect(_socket, &QTcpSocket::readyRead, this, &Session::onReadyRead);
    emit started(this);
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
    Network::Protocol::data_t headers_data = _socket->read(Network::Protocol::Headers::SIZE);
    Network::Protocol::Headers headers = Network::Serializer::deserialize<Network::Protocol::Headers>(headers_data);
    Network::Protocol::data_t data = _socket->read(headers.data_size);

    emit dataReceived(headers, data);
}
