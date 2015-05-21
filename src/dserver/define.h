/*
 * Define.h
 *
 *  Created on: 2013. 11. 28.
 *      Author: dongbum
 */

#ifndef DEFINE_H_
#define DEFINE_H_

#ifndef _WIN32_WINNT         
#define _WIN32_WINNT	0x0501
#endif 

#include <iostream>
#include <map>
#include <string>
#include <queue>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <tbb/concurrent_queue.h>

typedef boost::asio::io_service IoService;
typedef boost::asio::ip::tcp::endpoint EndPoint;
typedef boost::asio::ip::tcp::acceptor Acceptor;
typedef boost::asio::ip::tcp::socket Socket;

#endif /* DEFINE_H_ */
