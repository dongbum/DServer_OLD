#pragma once

#include "../define.h"

class SystemResourceMonitor
{
public:
	struct DiskSpaceInfo
	{
		DiskSpaceInfo(void)
		{
			memset(this, 0, sizeof(DiskSpaceInfo));
		};

		int64_t capacity;
		int64_t free;
		int64_t available;
	};

	static DiskSpaceInfo GetDiskSpaceInfo(std::string drive_name);
private:
};