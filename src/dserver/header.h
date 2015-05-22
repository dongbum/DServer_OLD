/*
 * Header.h
 *
 *  Created on: 2013. 11. 30.
 *      Author: dongbum
 */

#ifndef HEADER_H_
#define HEADER_H_

#include "define.h"

namespace dserver
{
class Header
{
public:
	Header(void)
	{
		total_length_ = 0;
		protocol_no_ = 0;
		data_length_ = 0;
	}

	int32_t		GetTotalLength(void)	{ return total_length_; };
	int32_t		GetProtocolNo(void)		{ return protocol_no_; };
	int32_t		GetDataLength(void)		{ return data_length_; };

private:
	int32_t		total_length_;
	int32_t		protocol_no_;
	int32_t		data_length_;
};

}

#endif /* HEADER_H_ */
