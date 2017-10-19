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
#include <boost/format.hpp>

#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <boost/serialization/singleton.hpp>

#include "json/json.h"

#include "config/config.h"

#include "logging/log_define.h"
#include "logging/log_manager.h"

#include "utility/util.h"
#include "utility/endian.h"

#include "container/thread_safe_queue.h"

typedef boost::asio::io_service			IoService;
typedef boost::asio::ip::tcp::endpoint	EndPoint;
typedef boost::asio::ip::tcp::acceptor	Acceptor;
typedef boost::asio::ip::tcp::socket	Socket;
typedef boost::system::error_code		ErrorCode;

typedef boost::mutex					Mutex;
typedef boost::lock_guard<Mutex>		LockGuard;

const int32_t kEND_MARKER = 19830419;

#define SVR							DServer::GetServerInstance()
#define GAME_SVR					std::static_pointer_cast<DServer>(SVR)

#define RECV_BUFFER_SIZE			1024 * 64		// 수신용 버퍼 크기
#define SEND_BUFFER_SIZE			1024 * 64		// 송신용 버퍼 크기
#define MAX_DATETIME_SIZE			(19+1)
