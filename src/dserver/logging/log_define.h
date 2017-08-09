#pragma once

#include "../define.h"


#define MAX_LOG_MESSAGE_LENGTH		1024

#define LL_DEBUG		dserver::logging::LOG_LEVEL_DEBUG
#define LL_INFO			dserver::logging::LOG_LEVEL_INFO
#define LL_WARN			dserver::logging::LOG_LEVEL_WARN
#define LL_ERROR		dserver::logging::LOG_LEVEL_ERROR
#define LL_FATAL		dserver::logging::LOG_LEVEL_FATAL
#define LL_MAX			dserver::logging::LOG_LEVEL_MAX

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