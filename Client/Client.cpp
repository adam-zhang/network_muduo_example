/********************************************************************************
> FileName:	Client.cpp
> Author:	Mingping Zhang
> Email:	mingpingzhang@163.com
> Create Time:	Fri Oct 20 10:34:30 2023
********************************************************************************/

#include "Client.h"
#include <muduo/base/Timestamp.h>
#include <muduo/base/Logging.h>
#include <iostream>

using namespace std;
using namespace muduo;
using namespace muduo::net;

Client::Client(EventLoop* loop, const InetAddress& serverAddr)
	: loop_(loop),
	client_(loop, serverAddr, "TimeClient")
{
	client_.setConnectionCallback(
			std::bind(&Client::onConnection, this, _1));
	client_.setMessageCallback(
			std::bind(&Client::onMessage, this, _1, _2, _3));
	// client_.enableRetry();
}

void Client::connect()
{
	client_.connect();
}

void Client::onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << conn->localAddress().toIpPort() << " -> "
		<< conn->peerAddress().toIpPort() << " is "
		<< (conn->connected() ? "UP" : "DOWN");

	if (!conn->connected())
	{
		loop_->quit();
	}
	else
	{
		conn->send("Hello Server");
	}
}

void Client::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime)
{
	muduo::string msg(buf->retrieveAllAsString());
	cout << msg << endl;
}
