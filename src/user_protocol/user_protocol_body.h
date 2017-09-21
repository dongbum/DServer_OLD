#pragma once

#include "../dserver/define.h"

typedef struct _PROTOCOL_BODY_ECHO
{
	_PROTOCOL_BODY_ECHO(void)
	{
		test_int16 = 0;
		test_int32 = 0;
		test_int64 = 0;
	}

	Header			header;
	int16_t			test_int16;
	int32_t			test_int32;
	int64_t			test_int64;
} PROTOCOL_BODY_ECHO;
