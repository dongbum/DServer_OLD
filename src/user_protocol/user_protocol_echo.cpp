#include "user_protocol.h"

namespace user_protocol
{

uint32_t UserProtocol::Echo(uint32_t& protocol_no, unsigned char* data, unsigned int& data_length)
{
	/*
	std::cout << "Echo" << std::endl;

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

	std::cout << "my_name    : " << my_name << std::endl;
	std::cout << "test_int16 : " << test_int16 << std::endl;
	std::cout << "test_int32 : " << test_int32 << std::endl;
	std::cout << "test_int64 : " << test_int64 << std::endl;
	*/

	std::cout << "Echo" << std::endl;

	PROTOCOL_BODY_ECHO* body_data = (PROTOCOL_BODY_ECHO*)data;
	std::cout << "my_name    : " << body_data->my_name << std::endl;
	std::cout << "test_int16 : " << body_data->test_int16 << std::endl;
	std::cout << "test_int32 : " << body_data->test_int32 << std::endl;
	std::cout << "test_int64 : " << body_data->test_int64 << std::endl;

	return 0;
}

}