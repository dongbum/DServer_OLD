#include "session.h"
#include "session_pool.h"


SessionPool::SessionPool(void)
{

}


SessionPool::~SessionPool(void)
{
	
}


void SessionPool::Init(Acceptor& acceptor, DServer* server, UserProtocol* user_protocol, uint32_t session_pool_count)
{
	for (int i = 0; i < session_pool_count; i++)
	{
		SessionPtr session = SessionPtr(new Session(acceptor.get_io_service(), server, user_protocol));

		session_queue_.Push(session);
	}
}


std::shared_ptr<Session> SessionPool::GetSession(void)
{
	SessionPtr session_ptr;
	session_ptr = session_queue_.Pop();

	return session_ptr;
}


void SessionPool::ReleaseSession(SessionPtr& session_ptr)
{
	session_queue_.Push(session_ptr);
}
