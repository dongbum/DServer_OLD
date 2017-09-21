#pragma once

#include <boost/thread.hpp>

class WorkThreadManager
{
public:
	WorkThreadManager(const unsigned int thread_count);
	virtual ~WorkThreadManager(void);

	void Run(void);
private:
	boost::thread_group thread_group_;
};
