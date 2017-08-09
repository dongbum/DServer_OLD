#pragma once

#include "../define.h"


#define MAX_LOG_MESSAGE_LENGTH		1024

#define LL_DEBUG(...)		LOG_MANAGER.Write(dserver::logging::LOG_LEVEL_DEBUG, __VA_ARGS__);
#define LL_INFO(...)		LOG_MANAGER.Write(dserver::logging::LOG_LEVEL_INFO, __VA_ARGS__);
#define LL_WARN(...)		LOG_MANAGER.Write(dserver::logging::LOG_LEVEL_WARN, __VA_ARGS__);
#define LL_ERROR(...)		LOG_MANAGER.Write(dserver::logging::LOG_LEVEL_ERROR, __VA_ARGS__);
#define LL_FATAL(...)		LOG_MANAGER.Write(dserver::logging::LOG_LEVEL_FATAL, __VA_ARGS__);


namespace dserver
{
namespace logging
{

enum LOG_LEVEL : short
{
	LOG_LEVEL_DEBUG = 0,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_FATAL,
	LOG_LEVEL_MAX
};

}
}