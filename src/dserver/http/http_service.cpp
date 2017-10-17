#include "http_service.h"

HTTPService::HTTPService(std::shared_ptr<Socket> socket_ptr)
	: socket_ptr_(socket_ptr)
{
}

HTTPService::~HTTPService(void)
{
}

void HTTPService::StartHandler(void)
{

}
