#ifndef __C_WORK_QUEUE_H__
#define __C_WORK_QUEUE_H__

#include "define.h"
#include "request_work.h"

namespace dserver
{

class WorkQueue
{
public:
	WorkQueue(void);
	virtual ~WorkQueue(void);

private:
	tbb::concurrent_queue<RequestWork> request_work_queue_;
};

}


#endif