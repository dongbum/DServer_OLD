#pragma once

#include "../define.h"
#include "http_define.h"

class HTTPResponse
{
public:

private:
	HTTP_STATUS_CODE status;
	std::vector<HTTP_HEADER> headers;
	std::string content;
};