#include "connectdialogviewmodel.h"
#include <qdir.h>

ConnectDialogViewModel::ConnectDialogViewModel(SessionManager* sessionManager, QObject* parent)
    : QObject(parent)
    , _sessionManager(sessionManager)
    , _host("127.0.0.1")
    , _port(8080)
    , _root("D:/")
    , _errorMessage()
{
}

void ConnectDialogViewModel::setHost(const QString& host)
{
    if (_host != host)
    {
        _host = host;
        emit hostChanged();
    }
}

void ConnectDialogViewModel::setPort(ushort port)
{
    if (_port != port)
    {
        _port = port;
        emit portChanged();
    }
}

void ConnectDialogViewModel::setRoot(const QString& root)
{
    if (_root != root)
    {
        _root = root;
        emit rootChanged();
    }
}

void ConnectDialogViewModel::setErrorMessage(const QString& errorMessage)
{
    if (_errorMessage != errorMessage)
    {
        _errorMessage = errorMessage;
        emit errorMessageChanged();
    }
}

Q_INVOKABLE void ConnectDialogViewModel::close()
{
    disconnect(_sessionManager, &SessionManager::started, this, &ConnectDialogViewModel::onStarted);
    disconnect(_sessionManager, &SessionManager::errorOccurred, this, &ConnectDialogViewModel::onErrorOccurred);

    emit closed();
}

Q_INVOKABLE void ConnectDialogViewModel::connectToHost()
{
    QString errorMessage = validate();
    if (!errorMessage.isEmpty())
    {
        setErrorMessage(errorMessage);
        return;
    }

    setErrorMessage("");
    _sessionManager->connectToHost(_host, _port, _root);

    connect(_sessionManager, &SessionManager::started, this, &ConnectDialogViewModel::onStarted);
    connect(_sessionManager, &SessionManager::errorOccurred, this, &ConnectDialogViewModel::onErrorOccurred);
}

void ConnectDialogViewModel::onStarted()
{
    setErrorMessage("");
    emit started();
}

void ConnectDialogViewModel::onErrorOccurred(QAbstractSocket::SocketError error, QString errorString)
{
    setErrorMessage(errorString);

    disconnect(_sessionManager, &SessionManager::started, this, &ConnectDialogViewModel::onStarted);
    disconnect(_sessionManager, &SessionManager::errorOccurred, this, &ConnectDialogViewModel::onErrorOccurred);
}

QString ConnectDialogViewModel::validate() const
{
    QString errorMessage;

    if (_host.isEmpty() || _port == 0 || _root.isEmpty())
        errorMessage += QString("Host must not be empty");

    if (_port == 0)
        errorMessage += QString("\nPort must be between 1 and 65535");

    if (_root.isEmpty())
        errorMessage += QString("\nRoot must not be empty");
    else if (!QDir(_root).exists())
        errorMessage += QString("\nRoot '%1' does not exist").arg(_root);

    return errorMessage;
}
