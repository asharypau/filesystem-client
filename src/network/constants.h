#ifndef NETWORK_CONSTANTS_H
#define NETWORK_CONSTANTS_H

#include "qbytearray.h"

namespace Network
{
using data_size_t = std::size_t;
using data_t = QByteArray;

static constexpr std::size_t DATA_SIZE = sizeof(Network::data_size_t);
} // namespace Network

#endif // NETWORK_CONSTANTS_H
