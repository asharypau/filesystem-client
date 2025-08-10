#include "sessionmanager.h"

SessionManager::SessionManager(Dispatcher* dispatcher, QObject* parent)
    : QObject(parent)
    , _dispatcher(dispatcher)
    , _session(nullptr)
{
}

void SessionManager::connectToHost(QString host, quint16 port, QString root)
{
    if (!_session)
    {
        _session = new Session(this);

        connect(_session, &Session::started, this, &SessionManager::onStarted);
        connect(_session, &Session::ended, this, &SessionManager::onEnded);
        connect(_session, &Session::errorOccurred, this, &SessionManager::onErrorOccurred);
    }

    _session->connectToHost(host, port, root);
}

void SessionManager::onStarted()
{
    connect(_session, &Session::dataReceived, _dispatcher, &Dispatcher::dispatch);

    emit started();
}

void SessionManager::onEnded()
{
    emit ended();
}

void SessionManager::onErrorOccurred(QAbstractSocket::SocketError error, QString errorString)
{
    emit errorOccurred(error, errorString);
}
