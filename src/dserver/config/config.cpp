/*
 * config.cpp
 *
 *  Created on: 2013. 11. 30.
 *      Author: dongbum
 */

#include "config.h"

namespace dserver
{
namespace config
{

ConfigManager::ConfigManager(void)
{

}


ConfigManager::~ConfigManager(void)
{

}


bool ConfigManager::Initialize(std::string file_name)
{
	Lock lock(rw_mutex_, true);

	std::cout << file_name << " Loading..." << std::endl;

	try
	{
		boost::property_tree::ini_parser::read_ini(file_name, ptree_);

		std::cout << "Load complete" << std::endl;
	}
	catch (boost::property_tree::ini_parser_error& error)
	{
		std::cout << "Load failed : " << error.message() << std::endl;
		return false;
	}

	return true;
}


ConfigManager::INI_Value ConfigManager::GetValue(std::string section_name, std::string key_name)
{
	try
	{
		return ptree_.get<ConfigManager::INI_Value>(section_name + "." + key_name);
	}
	catch (boost::property_tree::ptree_bad_path& error)
	{
		std::cout << "GetValue failed : " << error.what() << std::endl;
		exit(1);
	}
}


}
}


