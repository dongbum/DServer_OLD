#pragma once

#include "../define.h"


class ConfigManager : public boost::serialization::singleton<ConfigManager>
{
public:
	typedef tbb::spin_rw_mutex Mutex;
	typedef Mutex::scoped_lock Lock;

	typedef std::pair<std::string, std::string> INI_Key;
	typedef std::string INI_Value;
	typedef std::map<INI_Key, INI_Value> INI_Container;

	ConfigManager(void);
	virtual ~ConfigManager(void);

	bool Initialize(std::string file_name);
	ConfigManager::INI_Value GetValue(std::string section_name, std::string key_name);

public:
	static ConfigManager& GetMutableInstance(void) { return ConfigManager::get_mutable_instance(); }

private:
	boost::property_tree::ptree ptree_;
	INI_Container ini_data_;

private:
	Mutex rw_mutex_;

};


#define CONFIG_MANAGER_INSTANCE ConfigManager::GetMutableInstance()
