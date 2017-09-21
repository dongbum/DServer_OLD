#pragma once

#include "define.h"
#include "request_work.h"


class RequestWork;

class RequestWorkQueue
{
public:
	RequestWorkQueue(void);
	virtual ~RequestWorkQueue(void);

	void Push(const RequestWork& message);
	bool Pop(RequestWork& message);
	size_t Size(void);

private:
	tbb::concurrent_bounded_queue<RequestWork> request_work_queue_;

};
