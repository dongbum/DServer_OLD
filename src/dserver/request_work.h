#ifndef __C_REQUEST_WORK_H__
#define __C_REQUEST_WORK_H__

#include "define.h"
#include "server.h"

namespace dserver
{

class RequestWork
{
public:
	RequestWork(void);
	virtual ~RequestWork(void);

private:
	dserver::DServer::SessionPtr	session_;

};

}


#endif