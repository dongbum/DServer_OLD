#pragma once

#include "../define.h"
#include "log_define.h"

namespace dserver
{
namespace logging
{

	
class LogMessage
{
public:
	LogMessage(void)
	{
		memset(buffer_, 0, MAX_LOG_MESSAGE_LENGTH);
	}

	char* GetBuffer(void) { return buffer_; }

private:
	char buffer_[MAX_LOG_MESSAGE_LENGTH];

};


}
}