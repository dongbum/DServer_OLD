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
	try
	{
		boost::property_tree::ini_parser::read_ini(file_name, ptree_);
	}
	catch (boost::property_tree::ini_parser_error& error)
	{
		std::cout << error.message() << std::endl;
	}
}

Config::~Config(void)
{

}

INI_Value Config::GetValue(std::string section_name, std::string key_name)
{
	return ptree_.get<INI_Value>(section_name + "." + key_name);
}


}
}


