#ifndef REMOTECLIENT_H
#define REMOTECLIENT_H

#include "../core/constants.h"
#include "../services/serialization.h"
#include <qstring.h>

struct RemoteClient : public ISerializable<RemoteClient>
{
    QString id;
    bool isActive;

private:
    friend class ISerializable<RemoteClient>;

    data_size_t size_impl() const { return DATA_SIZE + id.size() + sizeof(isActive); }
    auto as_tuple_impl() { return std::tie(id, isActive); }
    auto as_tuple_impl() const { return std::tie(id, isActive); }
};

#endif // REMOTECLIENT_H
