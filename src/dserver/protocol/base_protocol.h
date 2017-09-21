#pragma once

#include "../define.h"
#include "../session/session.h"

class Session;
class BaseProtocol
{
public:
	typedef boost::function<uint32_t(Session*, uint32_t&, unsigned char*, unsigned int&)>		ProtocolFunction;
	typedef std::map<uint32_t, ProtocolFunction>									ProtocolMap;

	BaseProtocol(void);
	virtual ~BaseProtocol(void);

	bool			ExecuteProtocol(Session* session, uint32_t protocol_no, unsigned char* data, unsigned int& data_length);

protected:
	void			AddProtocol(uint32_t protocol_no, BaseProtocol::ProtocolFunction protocol_function);
	
private:
	ProtocolMap		protocol_map;

};
