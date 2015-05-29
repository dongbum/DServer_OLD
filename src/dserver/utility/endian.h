#ifndef _ENDIAN_H_
#define _ENDIAN_H_

#include "../define.h"

namespace dserver
{
namespace utility
{

// Network To Host
int8_t		ntoh(int8_t value);
int16_t		ntoh(int16_t value);
int32_t		ntoh(int32_t value);
int64_t		ntoh(int64_t value);

uint8_t		ntoh(uint8_t value);
uint16_t	ntoh(uint16_t value);
uint32_t	ntoh(uint32_t value);
uint64_t	ntoh(uint64_t value);

// Host To Network
int8_t		hton(int8_t value);
int16_t		hton(int16_t value);
int32_t		hton(int32_t value);
int64_t		hton(int64_t value);

uint8_t		hton(uint8_t value);
uint16_t	hton(uint16_t value);
uint32_t	hton(uint32_t value);
uint64_t	hton(uint64_t value);

}
}

#endif