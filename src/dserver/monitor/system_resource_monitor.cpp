#include "system_resource_monitor.h"

SystemResourceMonitor::DiskSpaceInfo SystemResourceMonitor::GetDiskSpaceInfo(std::string drive_name)
{
	DiskSpaceInfo disk_space_info;

	try
	{
		boost::filesystem::path path(drive_name.c_str());

		boost::filesystem::space_info space_info = boost::filesystem::space(path);

		disk_space_info.capacity = space_info.capacity;
		disk_space_info.free = space_info.free;
		disk_space_info.available = space_info.available;
	}
	catch (boost::filesystem::filesystem_error& ec)
	{
		
	}

	return disk_space_info;
}
