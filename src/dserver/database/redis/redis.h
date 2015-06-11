#ifndef _REDIS_H_
#define _REDIS_H_

#include "../../define.h"

namespace dserver
{
namespace database
{
namespace redis
{

class Redis
{
public:
	Redis(void);
	virtual ~Redis(void);

	bool	Connect(std::string& server_addr, std::string& server_port);
protected:

private:
	boost::asio::io_service		io_service_;
};

}
}
}

#endif