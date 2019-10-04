#include "../web_protocol.h"

std::string WebProtocol::GetDiskSpace(void)
{
	Json::Value root;
	root["description"] = "Get disk information.";
	Json::Value& disk_info_node = root["disk_info"];

#ifdef _WIN32
	char buffer[256] = { 0, };
	::GetLogicalDriveStringsA(256, buffer);

	std::string drive_name = "";

	for (int i = 0; i < 256; ++i)
	{
		drive_name = "";

		while (buffer[i] != '\0')
			drive_name += buffer[i++];

		if (drive_name.empty())
			continue;

		SystemResourceMonitor::DiskSpaceInfo disk_space_info = SystemResourceMonitor::GetDiskSpaceInfo(drive_name);
		
		Json::Value disk_info;
		disk_info["drive_name"] = drive_name;
		disk_info["capacity"] = disk_space_info.capacity;
		disk_info["free"] = disk_space_info.free;
		disk_info["available"] = disk_space_info.available;

		switch (::GetDriveTypeA(drive_name.c_str()))
		{
		case DRIVE_UNKNOWN:
			disk_info["drive_type"] = "DRIVE_UNKNOWN";
			break;
		case DRIVE_NO_ROOT_DIR:
			disk_info["drive_type"] = "DRIVE_NO_ROOT_DIR";
			break;
		case DRIVE_REMOVABLE:
			disk_info["drive_type"] = "DRIVE_REMOVABLE";
			break;
		case DRIVE_FIXED:
			disk_info["drive_type"] = "DRIVE_FIXED";
			break;
		case DRIVE_REMOTE:
			disk_info["drive_type"] = "DRIVE_REMOTE";
			break;
		case DRIVE_CDROM:
			disk_info["drive_type"] = "DRIVE_CDROM";
			break;
		case DRIVE_RAMDISK:
			disk_info["drive_type"] = "DRIVE_RAMDISK";
			break;
		default:
			disk_info["drive_type"] = "DRIVE_UNKNOWN";
			break;
		}

		if (0 == disk_space_info.available &&
			0 == disk_space_info.free &&
			0 == disk_space_info.capacity)
		{
			continue;
		}

		disk_info_node.append(disk_info);
	}
#else
	root["error"] = "This is an unsupported system.";

#endif

	return root.toStyledString();
}