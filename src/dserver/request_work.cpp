#include "request_work.h"

namespace dserver
{

RequestWork::RequestWork(void)
{

}

RequestWork::RequestWork(SessionPtr session, unsigned char buffer[])
{
	session_ = session;
	memcpy(buffer_, buffer, 1024);
}

RequestWork::~RequestWork(void)
{

}

}