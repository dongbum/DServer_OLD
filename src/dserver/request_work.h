#ifndef __C_REQUEST_WORK_H__
#define __C_REQUEST_WORK_H__

#include "define.h"
#include "server.h"
#include "session/session.h"

namespace dserver
{

class DServer;
class Session;

class RequestWork
{
public:
	typedef std::shared_ptr<Session>		SessionPtr;

	RequestWork(void);
	RequestWork(SessionPtr session, unsigned char buffer[]);
	virtual ~RequestWork(void);

private:
	SessionPtr			session_;
	unsigned char		buffer_[1024];
};

}


#endif