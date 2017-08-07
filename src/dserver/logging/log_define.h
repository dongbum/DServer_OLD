#pragma once

#include "../define.h"


#define MAX_LOG_MESSAGE_LENGTH		1024

namespace dserver
{
namespace logging
{

enum LOG_LEVEL : short
{
	LL_DEBUG = 0,
	LL_INFO,
	LL_WARN,
	LL_CRITICAL,
	LL_MAX
};

}
}