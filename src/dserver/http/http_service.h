#pragma once

#include "../define.h"

class HTTPService
{
public:
	HTTPService(std::shared_ptr<Socket> socket_ptr);
	virtual ~HTTPService(void);

	void StartHandler(void);

private:
	std::shared_ptr<Socket> socket_ptr_;

};