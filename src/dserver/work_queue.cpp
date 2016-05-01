#include "work_queue.h"

namespace dserver
{

WorkQueue::WorkQueue(void)
{

}

WorkQueue::~WorkQueue(void)
{

}

// ť�� �۾��� ����ִ´�.
void WorkQueue::Push(const RequestWork& message)
{
	request_work_queue_.push(message);
}

// ť���� �۾��� ���´�.
void WorkQueue::Task(RequestWork& message)
{
	request_work_queue_.try_pop(message);
}

}