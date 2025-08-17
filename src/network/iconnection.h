#ifndef NETWORK_ICONNECTION_H
#define NETWORK_ICONNECTION_H

#include "../models/client.h"
#include "protocol.h"
#include "protocoltypes.h"
#include <qobject.h>

namespace Network
{
class IConnection : public QObject
{
    Q_OBJECT

public:
    explicit IConnection(QObject* parent = nullptr)
        : QObject(parent) {};
    virtual ~IConnection() = default;

    virtual const LocalClient& owner() const = 0;
    virtual void writeHeaders(const Network::Protocol::Headers& headers) = 0;
    virtual void write(const Network::Protocol::data_t& data) = 0;
};
} // namespace Network

#endif // NETWORK_ICONNECTION_H