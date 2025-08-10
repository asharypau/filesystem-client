#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "dispatcher.h"
#include "session.h"
#include <qobject.h>

class SessionManager : public QObject
{
    Q_OBJECT

public:
    SessionManager(Dispatcher* dispatcher, QObject* parent = nullptr);

    void connectToHost(QString host, quint16 port, QString root);

signals:
    void started();
    void ended();
    void errorOccurred(QAbstractSocket::SocketError error, QString errorString);

private slots:
    void onStarted();
    void onEnded();
    void onErrorOccurred(QAbstractSocket::SocketError error, QString errorString);

private:
    Dispatcher* _dispatcher;
    Session* _session;
};

#endif // SESSIONMANAGER_H
