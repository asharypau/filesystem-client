#ifndef CONNECTDIALOGVIEWMODEL
#define CONNECTDIALOGVIEWMODEL

#include "../core/sessionmanager.h"
#include "qobject.h"

class ConnectDialogViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(ushort port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString root READ root WRITE setRoot NOTIFY rootChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage WRITE setErrorMessage NOTIFY errorMessageChanged)

public:
    ConnectDialogViewModel(SessionManager* sessionManager, QObject* parent = nullptr);

    QString host() const { return _host; }
    ushort port() const { return _port; }
    QString root() const { return _root; }
    QString errorMessage() const { return _errorMessage; }

    void setHost(const QString& host);
    void setPort(ushort port);
    void setRoot(const QString& root);
    void setErrorMessage(const QString& errorMessage);

    Q_INVOKABLE void close();
    Q_INVOKABLE void connectToHost();

signals:
    void hostChanged();
    void portChanged();
    void rootChanged();
    void errorMessageChanged();
    void closed();
    void started();

private slots:
    void onStarted();
    void onErrorOccurred(QAbstractSocket::SocketError error, QString errorString);

private:
    QString validate() const;

    SessionManager* _sessionManager;
    QString _host;
    quint16 _port;
    QString _root;
    QString _errorMessage;
};

#endif // CONNECTDIALOGVIEWMODEL
