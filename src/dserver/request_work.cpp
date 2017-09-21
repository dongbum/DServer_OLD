#include "request_work.h"


RequestWork::RequestWork(void)
	: session_(nullptr)
	, data_length_(0)
{
	memset(buffer_, 0, RECV_BUFFER_SIZE);
}

RequestWork::RequestWork(SessionPtr session, unsigned char buffer[], uint32_t length)
{
	session_ = session;

	if (length <= RECV_BUFFER_SIZE)
		memcpy(buffer_, buffer, length);

	data_length_ = length;
}

RequestWork::~RequestWork(void)
{

}
