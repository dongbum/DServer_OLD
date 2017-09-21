#pragma once

#include "define.h"
#include "server.h"
#include "session/session.h"


class DServer;
class Session;

class RequestWork
{
public:
	typedef std::shared_ptr<Session>		SessionPtr;

	RequestWork(void);
	RequestWork(SessionPtr session, unsigned char buffer[], uint32_t length);
	virtual ~RequestWork(void);

private:
	SessionPtr			session_;
	unsigned char		buffer_[1024];
	uint32_t			data_length_;
};
