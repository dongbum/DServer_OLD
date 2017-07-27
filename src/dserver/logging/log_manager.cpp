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


void LogManager::Run(void)
{
	while (true)
	{

	}
}

}
}