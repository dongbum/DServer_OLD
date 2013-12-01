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

Config::Config(std::string file_name)
{
	std::cout << file_name << " Loading..." << std::endl;

	try
	{
		boost::property_tree::ini_parser::read_ini(file_name, ptree_);

		std::cout << "Load complete" << std::endl;
	}
	catch (boost::property_tree::ini_parser_error& error)
	{
		std::cout << "Load failed : " << error.message() << std::endl;
	}
}

Config::~Config(void)
{

}

Config::INI_Value Config::GetValue(std::string section_name, std::string key_name)
{
	return ptree_.get<Config::INI_Value>(section_name + "." + key_name);
}


}
}


