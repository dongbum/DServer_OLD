/*
 * Define.h
 *
 *  Created on: 2013. 11. 28.
 *      Author: dongbum
 */

#ifndef DEFINE_H_
#define DEFINE_H_

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

typedef boost::asio::io_service IoService;
typedef boost::asio::ip::tcp::endpoint EndPoint;
typedef boost::asio::ip::tcp::acceptor Acceptor;
typedef boost::asio::ip::tcp::socket Socket;


#endif /* DEFINE_H_ */
