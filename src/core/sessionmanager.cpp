#include "sessionmanager.h"

SessionManager::SessionManager(QObject* parent)
    : QObject(parent)
    , _session(nullptr)
{
}

void SessionManager::connectToHost(QString host, quint16 port, QString root)
{
    if (!_session)
    {
        _session = new Session(this);

        connect(_session, &Session::started, this, &SessionManager::onStarted);
    }

    _session->connectToHost(host, port, root);
}

void SessionManager::onStarted(Network::IConnection* connection)
{
    connect(_session, &Session::ended, this, &SessionManager::onEnded);
    connect(_session, &Session::errorOccurred, this, &SessionManager::onErrorOccurred);
    connect(_session, &Session::dataReceived, this, &SessionManager::onDataReceived);

    emit started(connection);
}

void SessionManager::onEnded()
{
    emit ended();
}

void SessionManager::onErrorOccurred(QAbstractSocket::SocketError error, QString errorString)
{
    emit errorOccurred(error, errorString);
}

void SessionManager::onDataReceived(Network::Protocol::Headers headers, Network::Protocol::data_t data)
{
    emit dataReceived(headers, data);
}
