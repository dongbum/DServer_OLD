#include "work_queue.h"


RequestWorkQueue::RequestWorkQueue(void)
{

}

RequestWorkQueue::~RequestWorkQueue(void)
{

}


void RequestWorkQueue::Push(const RequestWork& message)
{
	request_work_queue_.push(message);
}


bool RequestWorkQueue::Pop(RequestWork& message)
{
	request_work_queue_.pop(message);

	return true;
}


size_t RequestWorkQueue::RequestWorkQueue::Size(void)
{
	return request_work_queue_.size();
}