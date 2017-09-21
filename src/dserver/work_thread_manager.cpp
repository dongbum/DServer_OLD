#include "work_thread_manager.h"
#include "../user_protocol/user_protocol.h"
#include "work_queue.h"


WorkThreadManager::WorkThreadManager(const unsigned int thread_count)
	: thread_count_(thread_count)
{

}


WorkThreadManager::~WorkThreadManager(void)
{

}


bool WorkThreadManager::SetUp(RequestWorkQueuePtr request_work_queue, UserProtocol* user_protocol)
{
	if (nullptr == request_work_queue)
		return false;

	if (nullptr == user_protocol)
		return false;

	request_work_queue_ = request_work_queue;
	user_protocol_ = user_protocol;

	return true;
}


void WorkThreadManager::Start(void)
{
	for (int i = 0; i < thread_count_; ++i)
	{
		boost::thread thread(boost::bind(&WorkThreadManager::Run, this, i));
		thread_group_.add_thread(&thread);
	}
}


void WorkThreadManager::Run(int16_t thread_no)
{
	if (nullptr == request_work_queue_ || nullptr == user_protocol_)
	{
		LL_DEBUG("WorkThreadManager Faild.");
		return;
	}

	LL_DEBUG("WorkThreadManager::Run - START");

	{
		LockGuard lock(logic_thread_mutex_);
		LL_DEBUG("WorkThreadManager::Run - ThreadNo:[%d]", thread_no);
	}

	while (true)
	{
		RequestWork request_work;

		if (true == request_work_queue_->Pop(request_work))
		{
			LL_DEBUG("RequestWork found. RequestWorkQueue size : %d", static_cast<int32_t>(request_work_queue_.get()->Size()));

			user_protocol_->ExecuteProtocol(request_work.GetSession(), request_work.GetProtocolNo(), request_work.GetData(), request_work.GetDataLength());
		}
	}
}
