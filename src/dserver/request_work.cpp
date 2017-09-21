#include "request_work.h"


RequestWork::RequestWork(void)
	: session_(nullptr)
	, protocol_no_(0)
	, data_length_(0)
{
	memset(buffer_, 0, RECV_BUFFER_SIZE);
}

RequestWork::RequestWork(std::shared_ptr<Session> session, int32_t protocol_no, unsigned char buffer[], uint32_t length)
{
	session_ = session;
	protocol_no_ = protocol_no;

	if (length <= RECV_BUFFER_SIZE)
		memcpy(buffer_, buffer, length);

	data_length_ = length;
}

RequestWork::~RequestWork(void)
{

}


std::shared_ptr<Session> RequestWork::GetSession(void)
{
	return session_;
}


int32_t RequestWork::GetProtocolNo(void)
{
	return protocol_no_;
}


unsigned char* RequestWork::GetData(void)
{
	return buffer_;
}


uint32_t RequestWork::GetDataLength(void)
{
	return data_length_;
}