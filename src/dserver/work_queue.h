#ifndef __C_WORK_QUEUE_H__
#define __C_WORK_QUEUE_H__

#include "define.h"
#include "request_work.h"

namespace dserver
{

class RequestWork;

class WorkQueue
{
public:
	WorkQueue(void);
	virtual ~WorkQueue(void);

	void Push(const RequestWork& message);
	void Task(RequestWork& message);

private:
	tbb::concurrent_bounded_queue<RequestWork> request_work_queue_;

};

}


#endif