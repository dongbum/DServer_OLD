#pragma once

#include "define.h"
#include "request_work.h"

namespace dserver
{

class RequestWork;

class RequestWorkQueue
{
public:
	RequestWorkQueue(void);
	virtual ~RequestWorkQueue(void);

	void Push(const RequestWork& message);
	void Pop(RequestWork& message);

private:
	tbb::concurrent_bounded_queue<RequestWork> request_work_queue_;

};

}
