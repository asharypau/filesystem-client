#ifndef CONNECTDIALOGVIEWMODEL
#define CONNECTDIALOGVIEWMODEL

#include <qobject.h>

class ConnectDialogViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(ushort port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString root READ root WRITE setRoot NOTIFY rootChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage WRITE setErrorMessage NOTIFY errorMessageChanged)

public:
    explicit ConnectDialogViewModel(QObject* parent = nullptr);

    QString host() const { return _host; }
    ushort port() const { return _port; }
    QString root() const { return _root; }
    QString errorMessage() const { return _errorMessage; }

    void setHost(const QString& host);
    void setPort(ushort port);
    void setRoot(const QString& root);
    void setErrorMessage(const QString& errorMessage);

    Q_INVOKABLE void connectToServer();

signals:
    void hostChanged();
    void portChanged();
    void rootChanged();
    void errorMessageChanged();
    void connectionSucceeded();

private:
    QString _host;
    ushort _port;
    QString _root;
    QString _errorMessage;
};

#endif // CONNECTDIALOGVIEWMODEL
