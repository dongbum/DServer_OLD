#include "work_queue.h"

namespace dserver
{

WorkQueue::WorkQueue(void)
{

}

WorkQueue::~WorkQueue(void)
{

}

// 큐에 작업을 집어넣는다.
void WorkQueue::Push(const RequestWork& message)
{
	request_work_queue_.push(message);
}

// 큐에서 작업을 빼온다.
void WorkQueue::Task(RequestWork& message)
{
	request_work_queue_.try_pop(message);
}

}