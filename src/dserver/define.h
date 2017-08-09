/*
 * Define.h
 *
 *  Created on: 2013. 11. 28.
 *      Author: dongbum
 */

#pragma once

#ifndef _WIN32_WINNT         
#define _WIN32_WINNT	0x0501
#endif

#ifndef CPPCONN_LIB_BUILD
#define CPPCONN_LIB_BUILD True
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <memory>

#include <locale.h>
#include <concurrent_queue.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/endian/conversion.hpp>
#include <boost/functional.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <boost/serialization/singleton.hpp>

#include <tbb/tbb.h>
#include <tbb/spin_rw_mutex.h>
#include <tbb/concurrent_queue.h>

#include "logging/log_define.h"
#include "logging/log_manager.h"

typedef boost::asio::io_service IoService;
typedef boost::asio::ip::tcp::endpoint EndPoint;
typedef boost::asio::ip::tcp::acceptor Acceptor;
typedef boost::asio::ip::tcp::socket Socket;

const int32_t kEND_MARKER = 19830419;


#define MAX_DATETIME_SIZE	(19+1)
