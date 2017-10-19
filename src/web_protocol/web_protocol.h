#pragma once

#include "../dserver/define.h"
#include "../dserver/http/http_base_protocol.h"

class WebProtocol : public HTTPBaseProtocol
{
public:
	WebProtocol(void) {};
	virtual ~WebProtocol(void) {};

	void Initialize(void)
	{
		// AddProtocol("/",						boost::bind(&WebProtocol::GetIndex, this, _1, _2, _3, _4));
		// AddProtocol("/info/disk_space",			boost::bind(&WebProtocol::GetDiskSpace, this, _1, _2, _3, _4));

		AddProtocol("/", boost::bind(&WebProtocol::GetIndex, this));
		AddProtocol("/info/disk_space", boost::bind(&WebProtocol::GetDiskSpace, this));
	};

	std::string GetIndex(void);
	std::string GetDiskSpace(void);
};