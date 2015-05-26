#ifndef _BASE_PROTOCOL_H_
#define _BASE_PROTOCOL_H_

#include "../define.h"

namespace dserver
{
namespace protocol
{

class BaseProtocol
{
public:
	typedef boost::function<uint32_t(uint32_t&, unsigned char*, unsigned int&)>		ProtocolFunction;
	typedef std::map<uint32_t, ProtocolFunction>									ProtocolMap;

	BaseProtocol(void);
	virtual ~BaseProtocol(void);

	bool			ExecuteProtocol(uint32_t protocol_no, unsigned char* data, unsigned int& data_length);

protected:
	void			AddProtocol(uint32_t protocol_no, BaseProtocol::ProtocolFunction protocol_function);
	
private:
	ProtocolMap		protocol_map;

};

}
}

#endif