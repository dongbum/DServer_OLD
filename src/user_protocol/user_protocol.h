#pragma once

#include "../dserver/define.h"
#include "../dserver/protocol/base_protocol.h"

#include "user_protocol_define.h"
#include "user_protocol_body.h"


class Session;
class UserProtocol : public BaseProtocol
{
public:
	UserProtocol(void);
	virtual ~UserProtocol(void);

	void		Initialize(void);

	uint32_t	Echo(Session* session, uint32_t& protocol_no, unsigned char* data, unsigned int& data_length);
};
