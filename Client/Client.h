/********************************************************************************
  > FileName:	Client.h
  > Author:	Mingping Zhang
  > Email:	mingpingzhang@163.com
  > Create Time:	Fri Oct 20 10:34:30 2023
 ********************************************************************************/
#ifndef CLIENT_H
#define CLIENT_H

#include <muduo/base/noncopyable.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpClient.h>

class Client : muduo::noncopyable
{
	public:
		Client(muduo::net::EventLoop* loop, const muduo::net::InetAddress& serverAddr);
		void connect();
	private:
		muduo::net::EventLoop* loop_;
		muduo::net::TcpClient client_;
	private:
		void onConnection(const muduo::net::TcpConnectionPtr& conn);
		void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp receiveTime);
};

#endif//CLIENT_H
