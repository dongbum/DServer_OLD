#ifndef _USER_PROTOCOL_BODY_H_
#define _USER_PROTOCOL_BODY_H_

#include "../dserver/define.h"

typedef struct _PROTOCOL_BODY_ECHO
{
	_PROTOCOL_BODY_ECHO(void)
	{
		memset(my_name, 0, sizeof(my_name));
		test_int16 = 0;
		test_int32 = 0;
		test_int64 = 0;
	}

	unsigned char	my_name[10];
	int16_t			test_int16;
	int32_t			test_int32;
	int64_t			test_int64;
} PROTOCOL_BODY_ECHO;

#endif