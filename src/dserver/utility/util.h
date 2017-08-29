#pragma once

#include "../define.h"

namespace dserver
{
namespace utility
{
class Util
{
std::string GetToday(void)
{
	const boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	const boost::format f = boost::format("%s-%02d-%02d")
		% now.date().year_month_day().year
		% now.date().year_month_day().month
		% now.date().year_month_day().day;

	return f.str();
}


std::string GetTime(void)
{
	const boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	const boost::format f = boost::format("%02d:%02d:%02d")
		% now.time_of_day().hours()
		% now.time_of_day().minutes()
		% now.time_of_day().seconds();

	return f.str();
}
};
}

namespace security
{
}
}
