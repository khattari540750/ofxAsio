#pragma once

#include "asio/asio.hpp"

namespace ofxAsio {
	class TcpSession {
	public:
		~TcpSession();
		static std::shared_ptr<TcpSession> make(asio::io_service& service);
		void start();
		asio::ip::tcp::socket& getSocket();
		char getTerminator();
		void setTerminator(char terminator);
		void addOnSendFn(std::function<void(std::string msg)> response);
		void addOnReceiveFn(std::function<void(std::string msg)> response);
	protected:
		TcpSession(asio::io_service& service);
		void setIncomingBufferSize(std::size_t buffer_size);
		void receive();
		void onWrite(const asio::error_code& error, std::size_t bytesReceived, std::string message);
		void onReceive(const asio::error_code& error, std::size_t bytesReceived);
		std::string mIncomingMessage;
		asio::ip::tcp::socket mSocket;
		bool mIsConnected;
		char mTerminator;
		std::vector<std::function<void(std::string msg)> > mOnSendFns;
		std::vector<std::function<void(std::string msg)> > mOnReceiveFns;
	};
}