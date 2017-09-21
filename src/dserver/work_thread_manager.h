#pragma once

#include "define.h"


class UserProtocol;
class RequestWorkQueue;
class WorkThreadManager
{
public:
	typedef std::shared_ptr<RequestWorkQueue>		RequestWorkQueuePtr;

	WorkThreadManager(const unsigned int thread_count);
	virtual ~WorkThreadManager(void);

	bool	SetUp(RequestWorkQueuePtr request_work_queue, UserProtocol* user_protocol);
	void	Start(void);
	void	Run(int16_t thread_no);

private:
	RequestWorkQueuePtr			request_work_queue_;
	UserProtocol*				user_protocol_;

	Mutex						logic_thread_mutex_;

	boost::thread_group			thread_group_;
	unsigned int				thread_count_;

};
