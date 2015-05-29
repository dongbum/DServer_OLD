#ifndef _USER_PROTOCOL_H_
#define _USER_PROTOCOL_H_

#include "../dserver/define.h"
#include "../dserver/protocol/base_protocol.h"

#include "user_protocol_define.h"
#include "user_protocol_body.h"

namespace user_protocol
{
class UserProtocol : public dserver::protocol::BaseProtocol
{
public:
	UserProtocol(void);
	virtual ~UserProtocol(void);

	void		Initialize(void);

	uint32_t	Echo(uint32_t& protocol_no, unsigned char* data, unsigned int& data_length);
};
}

#endif