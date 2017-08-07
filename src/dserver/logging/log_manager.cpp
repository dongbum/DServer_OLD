#include "log_manager.h"


namespace dserver
{
namespace logging
{


LogManager::LogManager(void)
{

}


LogManager::~LogManager(void)
{

}


bool LogManager::Init(void)
{
	log_thread_ = boost::thread(boost::bind(&LogManager::Run, this));

	return true;
}


void LogManager::Write(const char* format, ...)
{
	LogMessage log_message;

	va_list ap;
	va_start(ap, format);
	
	vsnprintf_s(log_message.GetBuffer(), MAX_LOG_MESSAGE_LENGTH, MAX_LOG_MESSAGE_LENGTH, format, ap);

	va_end(ap);

	log_queue_.try_push(log_message);
}


void LogManager::Run(void)
{
	while (true)
	{
		LogMessage log_message;

		if (log_queue_.try_pop(log_message))
		{
			std::cout << log_message.GetBuffer() << std::endl;
		}
	}
}

}
}