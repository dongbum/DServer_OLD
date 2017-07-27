#pragma once


#include "../define.h"
#include "log_message.h"

namespace dserver
{
namespace logging
{

class LogManager
{
public:
	LogManager(void);
	virtual ~LogManager(void);

	bool Init(void);

private:
	void Run(void);

private:
	tbb::concurrent_bounded_queue<LogMessage> log_queue_;
	boost::thread log_thread_;

};

}
}