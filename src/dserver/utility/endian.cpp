#include "endian.h"

namespace dserver
{
namespace utility
{

int8_t ntoh(int8_t value)
{
	return boost::endian::endian_reverse(value);
}

int16_t ntoh(int16_t value)
{
	return boost::endian::endian_reverse(value);
}

int32_t ntoh(int32_t value)
{
	return boost::endian::endian_reverse(value);
}

int64_t ntoh(int64_t value)
{
	return boost::endian::endian_reverse(value);
}

uint8_t ntoh(uint8_t value)
{
	return boost::endian::endian_reverse(value);
}

uint16_t ntoh(uint16_t value)
{
	return boost::endian::endian_reverse(value);
}

uint32_t ntoh(uint32_t value)
{
	return boost::endian::endian_reverse(value);
}

uint64_t ntoh(uint64_t value)
{
	return boost::endian::endian_reverse(value);
}


// Host To Network
int8_t hton(int8_t value)
{
	return boost::endian::endian_reverse(value);
}

int16_t hton(int16_t value)
{
	return boost::endian::endian_reverse(value);
}

int32_t hton(int32_t value)
{
	return boost::endian::endian_reverse(value);
}

int64_t hton(int64_t value)
{
	return boost::endian::endian_reverse(value);
}

uint8_t hton(uint8_t value)
{
	return boost::endian::endian_reverse(value);
}

uint16_t hton(uint16_t value)
{
	return boost::endian::endian_reverse(value);
}

uint32_t hton(uint32_t value)
{
	return boost::endian::endian_reverse(value);
}

uint64_t hton(uint64_t value)
{
	return boost::endian::endian_reverse(value);
}

}
}