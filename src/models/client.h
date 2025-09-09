#ifndef CLIENT_H
#define CLIENT_H

#include "../network/protocoltypes.h"
#include "../network/serialization.h"
#include "fileinfo.h"
#include "qlist.h"
#include "qstring.h"
#include <tuple>

class Client
{
public:
    using id_t = QString;

    Client::id_t id;
};

class LocalClient : public Client, public Network::ISerializable<LocalClient>
{
public:
    QString root;

private:
    friend class Network::ISerializable<LocalClient>;

    Network::Protocol::data_size_t size_impl() const
    {
        return sizeof(Network::Protocol::data_size_t) + id.size() + sizeof(Network::Protocol::data_size_t)
               + root.size();
    }

    auto as_tuple_impl() { return std::tie(id, root); }
    auto as_tuple_impl() const { return std::tie(id, root); }
};

class RemoteClient : public Client, public Network::ISerializable<RemoteClient>
{
public:
    bool isActive = false;

private:
    friend class Network::ISerializable<RemoteClient>;

    Network::Protocol::data_size_t size_impl() const
    {
        return sizeof(Network::Protocol::data_size_t) + id.size() + sizeof(isActive);
    }

    auto as_tuple_impl() { return std::tie(id, isActive); }
    auto as_tuple_impl() const { return std::tie(id, isActive); }
};

class ClientDirectoryInfo : public Client, public Network::ISerializable<ClientDirectoryInfo>
{
public:
    DirectoryInfo directoryInfo;

private:
    friend class Network::ISerializable<ClientDirectoryInfo>;
};

#endif // CLIENT_H
