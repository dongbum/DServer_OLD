#include "endian.h"


int8_t ntoh(int8_t value)
{
	return value;
}

int16_t ntoh(int16_t value)
{
	return boost::asio::detail::socket_ops::network_to_host_short(value);
}

int32_t ntoh(int32_t value)
{
	return boost::asio::detail::socket_ops::network_to_host_long(value);
}

int64_t ntoh(int64_t value)
{
	return (((int64_t)boost::asio::detail::socket_ops::network_to_host_long(static_cast<int32_t>(value))) << 32) + boost::asio::detail::socket_ops::network_to_host_long(value >> 32);
}

uint8_t ntoh(uint8_t value)
{
	return value;
}

uint16_t ntoh(uint16_t value)
{
	return boost::asio::detail::socket_ops::network_to_host_short(value);
}

uint32_t ntoh(uint32_t value)
{
	return boost::asio::detail::socket_ops::network_to_host_long(value);
}

uint64_t ntoh(uint64_t value)
{
	return (((int64_t)boost::asio::detail::socket_ops::network_to_host_long(static_cast<int32_t>(value))) << 32) + boost::asio::detail::socket_ops::network_to_host_long(value >> 32);
}


// Host To Network
int8_t hton(int8_t value)
{
	return value;
}

int16_t hton(int16_t value)
{
	return boost::asio::detail::socket_ops::host_to_network_short(value);
}

int32_t hton(int32_t value)
{
	return boost::asio::detail::socket_ops::host_to_network_long(value);
}

int64_t hton(int64_t value)
{
	return (((int64_t)boost::asio::detail::socket_ops::host_to_network_long(static_cast<int32_t>(value))) << 32) + boost::asio::detail::socket_ops::host_to_network_long(value >> 32);
}

uint8_t hton(uint8_t value)
{
	return value;
}

uint16_t hton(uint16_t value)
{
	return boost::asio::detail::socket_ops::host_to_network_short(value);
}

uint32_t hton(uint32_t value)
{
	return boost::asio::detail::socket_ops::host_to_network_long(value);
}

uint64_t hton(uint64_t value)
{
	return (((int64_t)boost::asio::detail::socket_ops::host_to_network_long(static_cast<int32_t>(value))) << 32) + boost::asio::detail::socket_ops::host_to_network_long(value >> 32);
}
