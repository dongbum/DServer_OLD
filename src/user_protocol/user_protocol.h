#pragma once

#include "../dserver/define.h"
#include "../dserver/protocol/base_protocol.h"

#include "user_protocol_define.h"
#include "user_protocol_body.h"


class Session;
class UserProtocol : public BaseProtocol
{
public:
	UserProtocol(void) {};
	virtual ~UserProtocol(void) {};

	void Initialize(void)
	{
		AddProtocol(UserProtocolNo::USER_PROTOCOL_ECHO, boost::bind(&UserProtocol::Echo, this, _1, _2, _3, _4));
	};

	uint32_t	Echo(std::shared_ptr<Session> session, uint32_t& protocol_no, unsigned char* data, uint32_t data_length);
};
