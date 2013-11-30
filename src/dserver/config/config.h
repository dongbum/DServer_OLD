/*
 * config.h
 *
 *  Created on: 2013. 11. 30.
 *      Author: dongbum
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "../define.h"

namespace dserver
{
namespace config
{

class Config
{
public:
	typedef std::pair<std::string, std::string> INI_Key;
	typedef std::string INI_Value;
	typedef std::map<INI_Key, INI_Value> INI_Container;

	Config(std::string file_name);
	virtual ~Config(void);

	INI_Value GetValue(std::string section_name, std::string key_name);
private:
	boost::property_tree::ptree ptree_;
	INI_Container ini_data_;
};

}
}



#endif /* CONFIG_H_ */
