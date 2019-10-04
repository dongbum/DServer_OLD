#pragma once

#include "../define.h"


class DServer;
class Session;
class UserProtocol;
class SessionPool
{
public:
	typedef std::shared_ptr<Session>		SessionPtr;
	typedef ThreadSafeQueue<SessionPtr>		SessionQueue;

	SessionPool(void);
	virtual ~SessionPool(void);

	void Init(Acceptor& acceptor, DServer* server, UserProtocol* user_protocol, uint32_t session_pool_count);

	std::shared_ptr<Session>	GetSession(void);
	void						ReleaseSession(SessionPtr& session_ptr);
	size_t						Size(void) { return session_queue_.Size(); }

private:
	ThreadSafeQueue<SessionPtr>		session_queue_;

};
