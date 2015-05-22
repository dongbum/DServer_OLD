#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "../define.h"

namespace dserver
{
namespace protocol
{

class Protocol
{
public:
	typedef std::map<uint32_t, int32_t>		ProtocolMap;

	Protocol(void);
	virtual ~Protocol(void);

protected:
	void AddProtocol(uint32_t, uint32_t);

private:
	ProtocolMap		protocol_map;

};

}
}

#endif