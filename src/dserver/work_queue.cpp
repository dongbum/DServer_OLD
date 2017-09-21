#include "work_queue.h"

namespace dserver
{

RequestWorkQueue::RequestWorkQueue(void)
{

}

RequestWorkQueue::~RequestWorkQueue(void)
{

}

// 큐에 작업을 집어넣는다.
void RequestWorkQueue::Push(const RequestWork& message)
{
	request_work_queue_.push(message);
}

// 큐에서 작업을 빼온다.
void RequestWorkQueue::Pop(RequestWork& message)
{
	request_work_queue_.try_pop(message);
}

}