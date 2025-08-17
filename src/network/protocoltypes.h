#ifndef NETWORK_PROTOCOLTYPES_H
#define NETWORK_PROTOCOLTYPES_H

#include "QByteArray"
#include <cstddef>

namespace Network
{
namespace Protocol
{
using data_size_t = std::size_t;
using data_t = QByteArray;
} // namespace Protocol
} // namespace Network

#endif // NETWORK_PROTOCOLTYPES_H
