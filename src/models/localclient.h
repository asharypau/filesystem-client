#ifndef LOCALCLIENT_H
#define LOCALCLIENT_H

#include "../network/constants.h"
#include "../network/serialization.h"
#include <qstring.h>

struct LocalClient : public Network::ISerializable<LocalClient>
{
    QString id;
    QString root;

private:
    friend class Network::ISerializable<LocalClient>;

    Network::data_size_t size_impl() const { return Network::DATA_SIZE + id.size() + Network::DATA_SIZE + root.size(); }
    auto as_tuple_impl() { return std::tie(id, root); }
    auto as_tuple_impl() const { return std::tie(id, root); }
};

#endif // LOCALCLIENT_H
