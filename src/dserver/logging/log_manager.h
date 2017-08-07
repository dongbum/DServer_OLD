#pragma once


#include "../define.h"
#include "log_message.h"

namespace dserver
{
namespace logging
{

class LogManager : public boost::serialization::singleton<LogManager>
{
public:
	LogManager(void);
	virtual ~LogManager(void);

	bool Init(void);
	void Write(const char* format, ...);

private:
	void Run(void);

public:
	static LogManager& GetMutableInstance(void) { return LogManager::get_mutable_instance(); }

private:
	tbb::concurrent_bounded_queue<LogMessage> log_queue_;
	boost::thread log_thread_;

};

}
}

#define LOG_MANAGER_INSTANCE dserver::logging::LogManager::GetMutableInstance()
#define LOG_MANAGER dserver::logging::LogManager::GetMutableInstance()