#ifndef LOCALCLIENT_H
#define LOCALCLIENT_H

#include "../core/constants.h"
#include "../services/serialization.h"
#include <qstring.h>

struct LocalClient : public ISerializable<LocalClient>
{
    QString id;
    QString root;

private:
    friend class ISerializable<LocalClient>;

    data_size_t size_impl() const { return DATA_SIZE + id.size() + DATA_SIZE + root.size(); }
    auto as_tuple_impl() { return std::tie(id, root); }
    auto as_tuple_impl() const { return std::tie(id, root); }
};

#endif // LOCALCLIENT_H
