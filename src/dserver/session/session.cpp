/*
 * Session.cpp
 *
 *  Created on: 2013. 11. 28.
 *      Author: dongbum
 */

#include "session.h"

namespace dserver
{

Session::Session(IoService& io_service, DServer* server)
:	socket_(io_service)
,	server_(server)
,	packet_buffer_size_(0)
{
	// TODO Auto-generated constructor stub
}

Session::~Session()
{
	// TODO Auto-generated destructor stub
}

Socket& Session::GetSocket()
{
	return socket_;
}

// Accept가 되면 처리할 함수
void Session::PostHandler(void)
{
	std::cout << "Session::PostHandler START" << std::endl;

	memset(recv_buffer_, 0, sizeof(recv_buffer_));

	// Recv를 한다.
	// ReceiveHandler로 처리를 넘긴다.

	socket_.async_read_some(
			boost::asio::buffer(recv_buffer_),
			boost::bind(
					&Session::ReceiveHandler,
					shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred
					)
			);
}

void Session::Init(WorkQueuePtr work_queue)
{
	work_queue_ = work_queue;
	user_protocol_manager.Initialize();
}

// Recv를 처리할 함수
void Session::ReceiveHandler(const boost::system::error_code& error, size_t bytes_transferred)
{
	std::cout << "Session::ReceiveHandler : bytes_transferred(" << bytes_transferred << ")" << std::endl;

	if (error)
	{
		if (error == boost::asio::error::eof)
		{
			std::cout << "Client connection end" << std::endl;
		}
		else
		{
			std::cout << "Client connection error : " << error.value() << " - msg : " << error.message() << std::endl;
		}

		// Recv가 실패하거나 소켓의 연결이 끊겼다면 소켓을 닫도록 한다.
		server_->CloseHandler(shared_from_this());
	}
	else
	{
		memcpy(&packet_buffer_[packet_buffer_size_], recv_buffer_, bytes_transferred);

		uint32_t packet_data_size = packet_buffer_size_ + static_cast<uint32_t>(bytes_transferred);
		uint32_t read_data = 0;

		while (packet_data_size > 0)
		{
			// 받은 데이터가 헤더보다 작다면 중지
			if (packet_data_size < sizeof(Header))
				break;

			// 헤더구하기
			Header* header = (Header*)&packet_buffer_[read_data];

			if (sizeof(Header) + header->GetDataLength() + sizeof(kEND_MARKER) <= packet_data_size)
			{
				int32_t end_marker_pos = sizeof(Header) + header->GetDataLength();

				// 엔드마커를 구한다.
				int32_t* end_marker = (int32_t*)(&packet_buffer_[end_marker_pos]);

				// 엔드마커를 확인해서 틀리다면 처리를 중지한다.
				if (kEND_MARKER != *end_marker)
				{
					std::cout << "END MARKER CHECK : FAIL" << std::endl;
					break;
				}

				// 데이터 처리
				// packet_buffer_[read_data];

				// PacketProcess(header->GetProtocolNo(), &packet_buffer_[sizeof(Header)], header->GetDataLength());

				std::cout << "Header.TotalLength : " << header->GetTotalLength() << std::endl;
				std::cout << "Header.ProtocolNo  : " << header->GetProtocolNo() << std::endl;
				std::cout << "Header.DataLength  : " << header->GetDataLength() << std::endl;

				packet_data_size = packet_data_size - header->GetDataLength();
				packet_data_size = packet_data_size - sizeof(kEND_MARKER);

				read_data = read_data + header->GetDataLength() + sizeof(kEND_MARKER);
			}
			else
			{
				break;
			}
		}

		if (packet_data_size > 0)
		{

		}

		packet_buffer_size_ = packet_data_size;

		/*
		std::cout << "Session::async_write" << std::endl;

		// WriteHandler를 이용해 데이터를 전송한다.
		char send_buffer[1024] = {0,};
		boost::asio::async_write(
				socket_,
				boost::asio::buffer(send_buffer),
				boost::bind(
						&Session::WriteHandler,
						this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred
						)
				);
		*/

		// 다시 PostHandler를 호출해서 Recv를 받는다.
		PostHandler();
	}
}

// 데이터를 전송한다.
void Session::WriteHandler(const boost::system::error_code& error, size_t bytes_transferred)
{
	std::cout << "Session::WriteHandler : bytes_transferred(" << bytes_transferred << ")" << std::endl;
}

void Session::PacketProcess(uint32_t protocol_no, unsigned char* packet_buffer, unsigned int& packet_length)
{
	// 프로토콜 바로 처리
	// user_protocol_manager.ExecuteProtocol(protocol_no, packet_buffer, packet_length);

	std::cout << "Push to work queue" << std::endl;

	work_queue_->Push(RequestWork(shared_from_this(), recv_buffer_));
}

}
