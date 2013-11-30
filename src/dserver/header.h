/*
 * Header.h
 *
 *  Created on: 2013. 11. 30.
 *      Author: dongbum
 */

#ifndef HEADER_H_
#define HEADER_H_

namespace dserver
{

const int32_t kEND_MARKER = 0x19830419;

class Header
{
public:
	Header(void)
	{
		total_length_ = 0;
		protocol_no_ = 0;
		data_length_ = 0;
		end_marker_ = kEND_MARKER;
	}
private:
	int32_t total_length_;
	int32_t protocol_no_;
	int32_t data_length_;

	int32_t end_marker_;
};

}

#endif /* HEADER_H_ */
