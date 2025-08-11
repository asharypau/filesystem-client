#ifndef REMOTECLIENT_H
#define REMOTECLIENT_H

#include "../network/constants.h"
#include "../network/serialization.h"
#include <qstring.h>

struct RemoteClient : public Network::ISerializable<RemoteClient>
{
    QString id;
    bool isActive;

private:
    friend class Network::ISerializable<RemoteClient>;

    Network::data_size_t size_impl() const { return Network::DATA_SIZE + id.size() + sizeof(isActive); }
    auto as_tuple_impl() { return std::tie(id, isActive); }
    auto as_tuple_impl() const { return std::tie(id, isActive); }
};

#endif // REMOTECLIENT_H
