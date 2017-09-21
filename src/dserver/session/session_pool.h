#pragma once

#include "../define.h"
#include "session.h"


class Session;

class SessionPool
{
public:
	typedef std::shared_ptr<Session>			SessionPtr;
	typedef tbb::concurrent_queue<SessionPtr>	SessionQueue;

	SessionPool(void);
	virtual ~SessionPool(void);

	void GetSession(void);
	void ReleaseSession(void);
};
