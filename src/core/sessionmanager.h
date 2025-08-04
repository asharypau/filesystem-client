#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "dispatcher.h"
#include <qobject.h>
#include <qtcpsocket.h>

class SessionManager : public QObject
{
    Q_OBJECT

public:
    SessionManager(Dispatcher* dispatcher, QObject* parent = nullptr);

    const QString& id() const { return _id; }
    const QString& root() const { return _root; }

    void connectToHost(QString host, quint16 port);

signals:
    void connected();
    void disconnected();
    void errorOccurred(QAbstractSocket::SocketError error, QString errorString);

private slots:
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError error);
    void onReadyRead();

private:
    Dispatcher* _dispatcher;
    QTcpSocket* _socket;

    QString _id;
    QString _root;
};

#endif // SESSIONMANAGER_H
