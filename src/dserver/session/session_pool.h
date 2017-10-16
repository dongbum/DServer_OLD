#pragma once

#include "../define.h"
#include "session.h"


class Session;

class SessionPool
{
public:
	typedef std::shared_ptr<Session>		SessionPtr;
	typedef ThreadSafeQueue<SessionPtr>		SessionQueue;

	SessionPool(Acceptor& acceptor, DServer* server, UserProtocol* user_protocol, const uint32_t session_pool_count);
	virtual ~SessionPool(void);

	std::shared_ptr<Session>	GetSession(void);
	void						ReleaseSession(SessionPtr& session_ptr);
	size_t						Size(void) { return session_queue_.Size(); }

private:
	ThreadSafeQueue<SessionPtr>		session_queue_;

};
