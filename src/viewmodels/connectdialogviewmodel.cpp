#include "connectdialogviewmodel.h"

ConnectDialogViewModel::ConnectDialogViewModel(QObject* parent)
    : QObject(parent)
    , _host()
    , _port(0)
    , _root()
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

Q_INVOKABLE void ConnectDialogViewModel::connectToServer()
{
    if (_host.isEmpty() || _port == 0 || _root.isEmpty())
    {
        setErrorMessage("Host and Port must not be empty.\nRoot must be between 1 and 65535.");
    }
    else
    {
        setErrorMessage("");
        emit connectionSucceeded();
    }
}
