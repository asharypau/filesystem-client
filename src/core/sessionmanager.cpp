#include "sessionmanager.h"
#include "../services/idgenerator.h"

SessionManager::SessionManager(Dispatcher* dispatcher, QObject* parent)
    : QObject(parent)
    , _dispatcher(dispatcher)
    , _socket(nullptr)
{
}

void SessionManager::connectToHost(QString host, quint16 port)
{
    if (!_socket)
    {
        _socket = new QTcpSocket(this);

        connect(_socket, &QTcpSocket::connected, this, &SessionManager::onConnected);
        connect(_socket, &QTcpSocket::errorOccurred, this, &SessionManager::onErrorOccurred);
    }

    _socket->abort();
    _socket->connectToHost(host, port);
}

void SessionManager::onConnected()
{
    _id = IdGenerator::generate(_root);

    connect(_socket, &QTcpSocket::disconnected, this, &SessionManager::onDisconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &SessionManager::onReadyRead);

    emit connected();
}

void SessionManager::onDisconnected()
{
    emit disconnected();
}

void SessionManager::onErrorOccurred(QAbstractSocket::SocketError error)
{
    emit errorOccurred(error, _socket->errorString());
}

void SessionManager::onReadyRead()
{
    QByteArray data = _socket->readAll();
    _dispatcher->dispatch(data);
}
