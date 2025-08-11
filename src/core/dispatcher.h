#ifndef DISPATCHERH_H
#define DISPATCHERH_H

#include <qobject.h>
#include <src/network/headerpackage.h>

class Dispatcher : public QObject
{
    Q_OBJECT

public:
    explicit Dispatcher(QObject* parent = nullptr);

    void dispatch(Network::HeaderPackage header_package, QByteArray data);

private:
    void handleClientListRequest(const QByteArray& data);
};

#endif // DISPATCHERH_H
