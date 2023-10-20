#include "Server.h"
#include <muduo/base/Logging.h>

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

// using namespace muduo;
// using namespace muduo::net;

Server::Server(muduo::net::EventLoop* loop,
		const muduo::net::InetAddress& listenAddr)
	: server_(loop, listenAddr, "Server")
{
	server_.setConnectionCallback(
			std::bind(&Server::onConnection, this, _1));
	server_.setMessageCallback(
			std::bind(&Server::onMessage, this, _1, _2, _3));
}

void Server::start()
{
	server_.start();
}

void Server::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
	LOG_INFO << "Server - " << conn->peerAddress().toIpPort() << " -> "
		<< conn->localAddress().toIpPort() << " is "
		<< (conn->connected() ? "UP" : "DOWN");
}

void Server::onMessage(const muduo::net::TcpConnectionPtr& conn,
		muduo::net::Buffer* buf,
		muduo::Timestamp time)
{
	muduo::string msg(buf->retrieveAllAsString());
	LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
		<< "data received at " << time.toString();
	conn->send(msg);
}

