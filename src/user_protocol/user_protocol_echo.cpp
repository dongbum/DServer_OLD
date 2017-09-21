#include "user_protocol.h"
#include "../dserver/session/session.h"


uint32_t UserProtocol::Echo(std::shared_ptr<Session> session, uint32_t& protocol_no, unsigned char* data, uint32_t data_length)
{
	/*
	wchar_t my_name[10 + 1] = { 0, };
	int16_t test_int16 = 0;
	int32_t test_int32 = 0;
	int64_t test_int64 = 0;

	int32_t index = 0;

	wcsncpy_s(my_name, (wchar_t*)data, 10);
	// memcpy(my_name, data + index, 14);
	index += 10;

	memcpy(&test_int16, data + index, sizeof(test_int16));
	index += sizeof(test_int16);

	memcpy(&test_int32, data + index, sizeof(test_int32));
	index += sizeof(test_int32);

	memcpy(&test_int64, data + index, sizeof(test_int64));
	index += sizeof(test_int64);

	*/

	LL_DEBUG("Echo");

	PROTOCOL_BODY_ECHO* body_data = (PROTOCOL_BODY_ECHO*)data;
	LL_DEBUG("test_int16 : %d", body_data->test_int16);
	LL_DEBUG("test_int32 : %d", body_data->test_int32);
	LL_DEBUG("test_int64 : %d", body_data->test_int64);

	return 0;
}
